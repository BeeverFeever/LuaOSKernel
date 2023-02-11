/**
 * Copyright (C) 2023 Amrit Bhogal
 *
 * This file is part of LuaOS.
 *
 * LuaOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LuaOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <limine.h>

#include "luck/io/log.h"


#include "luck/acpi/madt.h"
#include "luck/acpi/acpi.h"
#include "luck/arch/x86_64/gdt.h"
#include "luck/arch/x86_64/idt.h"
#include "luck/memory/manager.h"
#include "luck/memory/magazines.h"

attribute(used) noreturn void kernel_start()
{
    success("\nStarted LuaOS");
    info("{} + {} = {}", 2, 2, 2 + 2);
    info("Hello, {}", "World!");

    info("Initialising GDT");
    gdt_init();
    success("Done");

    info("Initialising IDT");
    // idt_init();
    success("Done");

    info("Initialising memory");
    {
        info("  Magazines...");
        magazine_init();
        success("  Done");

        info("  Kernel memory allocator...");
        kalloc_init();
        success("  Done");
    }
    success("Done");

    info("Initialising APIC");
    struct RSDP *rsdp = rsdp_init();
    if (rsdp == nullptr)
        panic("Could not find RSDP");

    struct MADT *madt = madt_init(rsdp);
    if (madt == nullptr) panic("Could not find MADT");

    size_t core_c = 0;

    for (struct MADTEntryHeader *entry = (struct MADTEntryHeader *)madt->entries;
         (uintptr_t)entry < (uintptr_t)(((uintptr_t)madt->entries) + madt->descriptor.length - sizeof(struct MADT));
         entry = (struct MADTEntryHeader *)((byte *)entry + (entry)->length)) {

        debug("  Found entry with ID {}", entry->id);
        switch (entry->id) {
            case MADT_ENTRY_ID_LAPIC: {
                struct MADTEntry_LAPIC *lapic = (struct MADTEntry_LAPIC *) entry;
                success("  Found LAPIC at core {} (address: {})", core_c++,
                        (void *) lapic);
                debug("    Processor ID: {}", lapic->processor_id);
                debug("    APIC ID: {}", lapic->apic_id);
                debug("    Flags: {}", lapic->flags);
                break;
            }
        }
    }
    success("Done");

    success("Initalisation complete");
    halt();
}
