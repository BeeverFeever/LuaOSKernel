//
// Created by Frityet on 2021-09-16.
//

#include "utilities.h"

void memset(void        *pointer,
            uintmax_t   value,
            uintmax_t   bytes)
{
    for (uint32_t i = 0; i < bytes; ++i) {
        ((char *)pointer)[i] = value;
    }
}

void memcpy(const int8_t        *src,
            int8_t              *dest,
            int                 byte_count)
{
    for (int i = 0; i < byte_count; ++i) {
        *(dest + i) = *(src + i);
    }
}



