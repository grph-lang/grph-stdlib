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
#include <stdbool.h>

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
    void *buffer;
} typedef grph_string_t;

struct grph_existential {
    struct typetable *type;
    void *data[3];
};

#define grph_optional_t(wrapped) struct { bool exists; wrapped value; }
#define GRPH_NULL {0}

typedef grph_optional_t(grph_integer_t) optional_integer_t;
typedef grph_optional_t(grph_float_t) optional_float_t;
typedef grph_optional_t(grph_pos_t) optional_pos_t;
typedef grph_optional_t(grph_string_t) optional_string_t;
typedef grph_optional_t(grph_rotation_t) optional_rotation_t;


#endif /* GRPH_TYPES_H */
