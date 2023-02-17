/**
 * Copyright (C) 2023 pitust
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

#include "memory.h"

void* memcpy(void *dst, const void *src, size_t n)
{ return memory_copy(dst, src, n); }

void* memset(void *dst, int c, size_t n)
{ return memory_set(dst, c, n); }

int memcmp(const void *b1, const void *b2, size_t n)
{ return memory_compare(b1, b2, n); }

void* memmove(void *dest, const void *src, size_t n)
{
    if (dest < src) {
        for (size_t i = 0; i < n; i++) {
            ((char *)dest)[i] = ((char *)src)[i];
        }
        return dest;
    } else {
        for (size_t i = n - 1; i < n; i++) {
            ((char *)dest)[i] = ((char *)src)[i];
        }
        return dest;
    }
}
