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

#include <stdio.h>

struct typetable *return_Group_typetable(void);
struct typetable *return_shape_array_typetable(void);

grph_Group_t *grphc_Group(bool name_exists, grph_string_t name, optional_integer_t zpos, bool rotation_exists, grph_rotation_t rotation, grph_array_t *shapes)
{
    grph_Group_t *this = alloc_box(sizeof(grph_Group_t));

    this->superclass.isa = return_Group_typetable();
    if (shapes)
        grphvwt_retain_ref(&this->shapes, &shapes, return_shape_array_typetable());
    else
        this->shapes = grpharr_create(return_shape_array_typetable(), 0);

    // TODO: implement name, zpos and rotation
    return this;
}

grph_array_t *grphp_Group_shapes_get(grph_Group_t *this)
{
    retain_box(this->shapes);
    return this->shapes;
}

void grphd_Group(grph_Group_t *bg)
{
    grphvwt_release_ref(&bg->shapes, return_shape_array_typetable());
    dealloc_box(bg);
}
