//
//  Background.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 06/06/2023.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_shapes.h"
#include "box.h"
#include "vwt.h"
#include "shape_witness.h"

struct typetable *return_Background_typetable(void);
struct typetable *return_shape_array_typetable(void);

struct shape_witness_table grphswt_Background = {
    .size_offset = offsetof(grph_Background_t, size),
    .paint_offset = offsetof(grph_Background_t, paint),
};

grph_Background_t *grphc_Background(grph_pos_t size, struct grph_existential *paint)
{
    grph_Background_t *bg = alloc_box(sizeof(grph_Background_t));

    bg->superclass.superclass.isa = return_Background_typetable();
    bg->superclass.shapes = grpharr_create(return_shape_array_typetable(), 0);
    bg->size = size;
    bg->paint = *paint;
    return bg;
}

void grphd_Background(grph_Background_t *bg)
{
    grphvwt_destroy_mixed(&bg->paint, bg->paint.type);
    grphd_Group(&bg->superclass);
}
