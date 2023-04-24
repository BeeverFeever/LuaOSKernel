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

#pragma once

#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>

#if __STDC_VERSION__ > 201710L
#define C2X true
#else
#define C2X false
#endif

#define closed_enum enum [[clang::enum_extensibility(closed)]]

#define pragma(...) _Pragma(#__VA_ARGS__)
#define asm __asm__ __volatile__

#define NONNULL_BEGIN pragma(clang assume_nonnull begin)
#define NONNULL_END pragma(clang assume_nonnull end)

#define auto __auto_type

#define assert_nonnull(...) ({          \
    auto _val = (__VA_ARGS__);          \
    if (_val == 0) _ASSERT_NONNULL

#define _ASSERT_NONNULL(...)            \
    __VA_ARGS__;                     \
  (typeof(typeof(*_val) *nonnull))_val; \
  })



typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

typedef int8_t sbyte;
/**
 * @attention This is literally the only reason why I forced usage of *word,
 * because then we can have "sword" and thats really cool
 */
typedef int16_t sword;
typedef int32_t sdword;
typedef int64_t sqword;

typedef const void *label;

//[[noreturn]]
static inline noreturn void halt() {
    while (true)
        asm("STI\n"
            "HLT\n");
    __builtin_unreachable();
}
