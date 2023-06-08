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
#include "existentials.h"
#include "typetable.h"
#include "box.h"
#include "ownership.h"
#include "vwt.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

struct typetable *return_Background_typetable(void);
struct typetable *return_shape_array_typetable(void);

grph_Background_t *grphc_Background(grph_pos_t size, struct grph_existential *paint)
{
    grph_Background_t *bg = alloc_box(sizeof(grph_Background_t));

    bg->superclass.superclass.isa = return_Background_typetable();
    bg->superclass.shapes = grpharr_create(return_shape_array_typetable(), 0);
    bg->size = size;
    bg->paint = *paint;
    return bg;
}

void grphd_Group(grph_Group_t *bg)
{
    grphvwt_release_ref(&bg->shapes, return_shape_array_typetable());
    dealloc_box(bg);
}

void grphd_Background(grph_Background_t *bg)
{
    grphvwt_destroy_mixed(&bg->paint, bg->paint.type);
    grphd_Group(&bg->superclass);
}

void grphvwt_release_Group(void *_value, struct typetable *type)
{
    (void) type;
    grph_Group_t *bg = *(grph_Group_t **) _value;

    if (release_box(bg)) {
        grphd_Group(bg);
    }
}

void grphvwt_release_Background(void *_value, struct typetable *type)
{
    (void) type;
    grph_Background_t *bg = *(grph_Background_t **) _value;

    if (release_box(bg)) {
        grphd_Background(bg);
    }
}
