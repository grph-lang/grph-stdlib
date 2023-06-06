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

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

struct typetable *return_Background_typetable(void);

grph_Background_t *grphc_Background(grph_pos_t size, struct grph_existential paint)
{
    grph_Background_t *bg = alloc_box(sizeof(grph_Background_t));
    
    bg->isa = return_Background_typetable();
    bg->size = size;
    bg->paint = paint;
    return bg;
}
