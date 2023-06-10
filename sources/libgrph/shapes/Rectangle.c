//
//  Rectangle.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 09/06/2023.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_shapes.h"
#include "box.h"
#include "vwt.h"
#include "shape_witness.h"

struct typetable *return_Rectangle_typetable(void);

struct shape_witness_table grphswt_Rectangle = {
    .pos_offset = offsetof(grph_Rectangle_t, pos),
    .zpos_offset = offsetof(grph_Rectangle_t, zpos),
    .size_offset = offsetof(grph_Rectangle_t, size),
    .rotation_offset = offsetof(grph_Rectangle_t, rotation),
    .paint_offset = offsetof(grph_Rectangle_t, paint),
    .strokeWrapper_offset = offsetof(grph_Rectangle_t, strokeWrapper),
};

static void init_stroke_wrapper(struct stroke_wrapper *this,
    bool strokeWidth_exists, grph_float_t strokeWidth,
    optional_stroke_t stroke,
    optional_array_t strokeDashArray)
{
    this->filling = !(strokeWidth_exists || stroke.exists || strokeDashArray.exists);
    this->strokeWidth = strokeWidth_exists ? strokeWidth : 5;
    this->stroke = GRPH_OPTIONAL_OR(stroke, GRPH_STROKE_ELONGATED);
    this->strokeDashArray = GRPH_OPTIONAL_OR(strokeDashArray, NULL);
}

grph_Rectangle_t *grphc_Rectangle(
    bool name_exists, grph_string_t name,
    grph_pos_t pos,
    optional_integer_t zpos,
    grph_pos_t size,
    bool rotation_exists, grph_rotation_t rotation,
    struct grph_existential *paint,
    bool strokeWidth_exists, grph_float_t strokeWidth,
    optional_stroke_t stroke,
    optional_array_t strokeDashArray)
{
    grph_Rectangle_t *this = alloc_box(sizeof(grph_Rectangle_t));

    this->superclass.isa = return_Rectangle_typetable();
    this->pos = pos;
    this->zpos = GRPH_OPTIONAL_OR(zpos, 0);
    this->size = size;
    this->rotation = rotation_exists ? rotation : 0;
    this->paint = *paint;
    init_stroke_wrapper(&this->strokeWrapper, strokeWidth_exists, strokeWidth, stroke, strokeDashArray);
    return this;
}

void grphd_Rectangle(grph_Rectangle_t *this)
{
    grphvwt_destroy_mixed(&this->paint, this->paint.type);
    if (this->strokeWrapper.strokeDashArray) {
        grphvwt_release_ref(this->strokeWrapper.strokeDashArray, this->strokeWrapper.strokeDashArray->isa);
    }
    dealloc_box(this);
}
