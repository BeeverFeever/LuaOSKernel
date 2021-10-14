//
// Created by Frityet on 2021-10-08.
//

#include "pmm.h"
#include "drivers/logger.h"
#include <common.h>

struct pmm physical_memory_manager;

static lock_t pmm_lock;


void initialise_pmm(struct stivale2_struct *bootloader)
{
    logger.writeln("Initialising Physical Memory Manager");

    {
        struct stivale2_struct_tag_memmap *tag = (struct stivale2_struct_tag_memmap *) get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_MEMMAP_ID);
        physical_memory_manager.memory_map = tag->memmap;
        physical_memory_manager.entry_count = tag->entries;
    }

    logger.writeln("Setting top page");
    //Set top page
    for (int i = 0; i < physical_memory_manager.entry_count; ++i) {
        struct stivale2_mmap_entry entry = physical_memory_manager.memory_map[i];
        /*
        string  index   = strnum(i, BASE_10),
                base    = strnum(entry.base, BASE_16),
                length  = strnum(entry.length, BASE_10),
                type    = strnum(entry.type, BASE_10);

        logger.writefln("Memory Map Entry %", index);
        logger.writefln("Base:      %", base);
        logger.writefln("Length:    %", length);
        logger.writefln("Type:      %", type);
         */
        if (entry.type != STIVALE2_MMAP_USABLE
        &&  entry.type != STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE
        &&  entry.type != STIVALE2_MMAP_KERNEL_AND_MODULES)
            continue;

        uintptr_t top = entry.base + entry.length;
        if (top > physical_memory_manager.top_page) {
            physical_memory_manager.top_page = top;
        }
    }

    logger.writefln("Initalising bitmap");
    //Set bitmap
    size_t bitmap_size = ROUND_UP(physical_memory_manager.top_page / PAGE_SIZE, 8);
    for (int i = 0; i < physical_memory_manager.entry_count; ++i) {
        struct stivale2_mmap_entry entry = physical_memory_manager.memory_map[i];
        if (entry.type != STIVALE2_MMAP_USABLE || entry.length < bitmap_size)
            continue;


        physical_memory_manager.bitmap = (uint8_t *)entry.base + PHYSICAL_BASE_ADDRESS;
        size_t bm_pages = ROUND_UP(bitmap_size, PAGE_SIZE);

        memset(physical_memory_manager.bitmap, 0xFF, bitmap_size);

        //Val not ref
        physical_memory_manager.memory_map[i].base   += bm_pages * PAGE_SIZE;
        physical_memory_manager.memory_map[i].length -= bm_pages * PAGE_SIZE;
        break;
    }

    logger.writeln("Populating Bitmap");
    //Populate bitmap
    for (int i = 0; i < physical_memory_manager.entry_count; ++i) {
        struct stivale2_mmap_entry entry = physical_memory_manager.memory_map[i];
        if (entry.type != STIVALE2_MMAP_USABLE)
            continue;

        size_t  page_num    = entry.base / PAGE_SIZE,
                length      = entry.length / PAGE_SIZE;

        for (size_t j = page_num; j <= page_num + length; ++j) {
            clear_bit(physical_memory_manager.bitmap, j);
        }
    }

    physical_memory_manager.alloc = &alloc;
    physical_memory_manager.free = &free;
    physical_memory_manager.get_free_memory = &get_free_memory;
    logger.writeln("Done");
}

static voidptr alloc(size_t size)
{
    size_t count = 0;

    acquire_lock(&pmm_lock);

    for (int i = 0; i < physical_memory_manager.bitmap_size * 8; ++i) {
        if (is_bit_set(physical_memory_manager.bitmap, i)) {
            ++count;

            if (count == size) {
                uintptr_t page = i - size + 1;

                for (int j = page; j < page + size; ++j) {
                    set_bit(physical_memory_manager.bitmap, j);
                }

                memaddr_t address = page * PAGE_SIZE;
                memset((voidptr) (address + PHYSICAL_BASE_ADDRESS), 0, size + PAGE_SIZE);

                release_lock(&pmm_lock);
                return (voidptr)address;
            }
        } else {
           count = 0;
        }
    }

    release_lock(&pmm_lock);

    return NULL;
}

static void free(voidptr ptr, size_t size)
{
    uintptr_t page = (uintptr_t)ptr / PAGE_SIZE;

    acquire_lock(&pmm_lock);

    for (uintptr_t i = page; i < page + size; ++i) {
        clear_bit(physical_memory_manager.bitmap, i);
    }

    release_lock(&pmm_lock);
}

static uint64_t get_free_memory(void)
{
    uint64_t free_pages = 0;

    for (size_t i = 0; i < physical_memory_manager.bitmap_size * 8; i++) {
        if (is_bit_set(physical_memory_manager.bitmap, i)) {
            ++free_pages;
        }
    }

    return free_pages * PAGE_SIZE;
}

inline void clear_bit(uint8_t *bitmap, uintptr_t bit)
{
    bitmap[bit / 8] |= (1 << (7 - bit % 8));
}

inline bool is_bit_set(const uint8_t *bitmap, uintptr_t bit)
{
    if (bitmap[bit/8] & (1 << (7 - bit%8))) {
        return true;
    }

    return false;
}

inline void set_bit(uint8_t *bitmap, uintptr_t bit)
{
    bitmap[bit / 8] |= (1 << (7 - bit % 8));
}
