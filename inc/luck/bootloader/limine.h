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

#include <limine/limine.h>

#include "common.h"

NONNULL_BEGIN

#define BOOTLOADER_MODULE(name) \
    extern const volatile struct limine_##name##_response *nullable bootloader_##name

BOOTLOADER_MODULE(hhdm);
BOOTLOADER_MODULE(kernel_address);
BOOTLOADER_MODULE(module);
BOOTLOADER_MODULE(framebuffer);
BOOTLOADER_MODULE(rsdp);
BOOTLOADER_MODULE(memmap);

#undef BOOTLOADER_MODULE

void bootloader_init(void);

qword limine_virt_to_phys(qword virt);
qword limine_phys_to_virt(qword phys);

#define phys(value) limine_virt_to_phys((qword)(value))
#define virt(value, ...)                                                       \
  (__VA_OPT__((__VA_ARGS__ *))(qword) limine_phys_to_virt(value))

NONNULL_END
