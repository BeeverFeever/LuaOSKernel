/**
 * @file    pmm.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Physical memory manager, allows for the allocation of pages
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */
#ifndef LUAOS_PMM
#define LUAOS_PMM

#include <common.h>

#define PAGE_SIZE               (2 << 11)
//#define PHYSICAL_BASE_ADDRESS   0xFFFF800000000000

extern struct pmm {
    struct stivale2_mmap_entry  *memory_map;
    uint64_t                    memory_map_entry_count;
    byte_t                      *bitmap;
    quadword_t                  last_page;
    size_t                      bitmap_size;
    uint64_t                    physical_base_address;
} physical_memory_manager;

struct allocation_header {
    size_t      size;
    voidptr_t   data;
};

void initialise_pmm(struct stivale2_struct *bootloader);
voidptr_t pmm_memalloc(size_t size);
void pmm_free(voidptr_t ptr);
size_t get_free_memory(void);

UNUSED static inline struct allocation_header *headerof(voidptr_t ptr)
{
    return ptr - sizeof(struct allocation_header);
}

#endif //LUAOS_PMM
