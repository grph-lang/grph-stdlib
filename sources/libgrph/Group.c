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

struct typetable *return_Group_typetable(void);
struct typetable *return_shape_array_typetable(void);

void grphd_Group(grph_Group_t *bg)
{
    grphvwt_release_ref(&bg->shapes, return_shape_array_typetable());
    dealloc_box(bg);
}
