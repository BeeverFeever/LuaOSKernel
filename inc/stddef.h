#pragma once

#include <stdint.h>

#define bool _Bool
#define true 1
#define false 0

typedef unsigned long size_t;
typedef long ssize_t;

#define NULL ((void*)0)
#define nullptr ((void*)0)

#define offsetof(s, m) __builtin_offsetof(s, m)
