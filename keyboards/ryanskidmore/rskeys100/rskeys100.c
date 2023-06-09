// Copyright 2021 Ryan Skidmore (@ryanskidmore, rskeys@ryanskidmore.co.uk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {   0,      1,   2,   3,      4,      5,   6,      7,      8,      9,  10, 11, 12, NO_LED,     13,     14,     15, NO_LED, NO_LED, NO_LED, NO_LED },
        {  36,     35,  34,  33,     32,     31,  30,     29,     28,     27,  26, 25, 24,     23,     22,     21,     20,     19,     18,     17,     16 },
        {  37,     38,  39,  40,     41,     42,  43,     44,     45,     46,  47, 48, 49,     50,     51,     52,     53,     54,     55,     56,     57 },
        {  73,     72,  71,  70,     69,     68,  67,     66,     65,     64,  63, 62, 61, NO_LED, NO_LED, NO_LED, NO_LED,     60,     59,     58, NO_LED },
        {  74,     75,  76,  77,     78,     79,  80,     81,     82,     83,  84, 85, 86, NO_LED, NO_LED,     87, NO_LED,     88,     89,     90,     91 },
        { 104, NO_LED, 103, 102, NO_LED, NO_LED, 101, NO_LED, NO_LED, NO_LED, 100, 99, 98,     97,     96,     95,    94,     93, NO_LED,     92, NO_LED }
    }, {
        { 0,  0 }, { 21,  0 }, { 32,  0 }, { 43,  0 }, {  53,  0 }, {  64,  0 }, {  75,  0 }, {  85,  0 }, {  96,  0 }, { 117,  0 }, { 128,  0 }, { 139,  0 }, { 149,  0 }, { 160,  0 }, { 171,  0 }, { 181,  0 },
        { 0, 13 }, { 11, 13 }, { 21, 13 }, { 32, 13 }, {  42, 13 }, {  53, 13 }, {  64, 13 }, {  75, 13 }, {  85, 13 }, {  96, 13 }, { 107, 13 }, { 117, 13 }, { 128, 13 }, { 139, 13 }, { 160, 13 }, { 171, 13 }, { 181, 13 }, { 192, 13 }, { 203, 13 }, { 213, 13 }, { 224, 13 },
        { 0, 26 }, { 11, 26 }, { 21, 26 }, { 32, 26 }, {  42, 26 }, {  53, 26 }, {  64, 26 }, {  75, 26 }, {  85, 26 }, {  96, 26 }, { 107, 26 }, { 117, 26 }, { 128, 26 }, { 149, 26 }, { 160, 26 }, { 171, 26 }, { 181, 26 }, { 192, 26 }, { 203, 26 }, { 213, 26 }, { 224, 26 },
        { 0, 38 }, { 11, 38 }, { 21, 38 }, { 32, 38 }, {  42, 38 }, {  53, 38 }, {  64, 38 }, {  75, 38 }, {  85, 38 }, {  96, 38 }, { 117, 38 }, { 128, 38 }, { 149, 38 }, { 192, 38 }, { 203, 38 }, { 213, 38 },
        { 0, 51 }, { 11, 51 }, { 21, 51 }, { 32, 51 }, {  42, 51 }, {  53, 51 }, {  64, 51 }, {  75, 51 }, {  85, 51 }, {  96, 51 }, { 107, 51 }, { 117, 51 }, { 139, 51 }, { 171, 51 }, { 192, 51 }, { 203, 51 }, { 213, 51 }, { 224, 51 },
        { 0, 64 }, { 11, 64 }, { 21, 64 }, { 64, 64 }, { 107, 64 }, { 117, 64 }, { 128, 64 }, { 149, 64 }, { 160, 64 }, { 171, 64 }, { 181, 64 }, { 192, 64 }, { 213, 64 }
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};
#endif
