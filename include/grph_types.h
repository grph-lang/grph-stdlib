//
//  grph_types.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 26/01/2022.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef GRPH_TYPES_H
#define GRPH_TYPES_H

#include <stdint.h>

typedef int64_t grph_integer_t;
typedef double grph_float_t;
typedef float grph_rotation_t;
typedef char grph_boolean_t;

struct {
    grph_float_t x;
    grph_float_t y;
} typedef grph_pos_t;

struct {
    uint64_t metadata;
    char *buffer;
} typedef grph_string_t;

#define STR_LEN(str) ((str).metadata & ~(1ULL << 63))

#endif /* GRPH_TYPES_H */
