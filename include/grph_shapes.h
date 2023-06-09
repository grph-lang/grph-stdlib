//
//  grph_shapes.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 06/06/2023.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef GRPH_SHAPES_H
#define GRPH_SHAPES_H

#include "grph_types.h"
#include "typetable.h"
#include "grph_array.h"

struct {
    // as all reference types
    struct typetable *isa;
} typedef grph_shape_t;

struct {
    // superclass: grph_shape_t
    grph_shape_t superclass;

    // the shapes in this group
    grph_array_t *shapes;
} typedef grph_Group_t;

struct {
    // superclass: grph_Group_t
    grph_Group_t superclass;

    // the size of the window, in pixels
    grph_pos_t size;
    // the background paint of the window
    struct grph_existential paint;
} typedef grph_Background_t;

struct {
    // superclass: grph_shape_t
    grph_shape_t superclass;

    grph_pos_t pos;
    grph_integer_t zpos;
    grph_pos_t size;
    grph_rotation_t rotation;
    struct grph_existential paint;
    grph_boolean_t filling;
    grph_float_t strokeWidth;
    grph_stroke_t stroke;
    grph_array_t *strokeDashArray;
} typedef grph_Rectangle_t;

#endif /* GRPH_SHAPES_H */
