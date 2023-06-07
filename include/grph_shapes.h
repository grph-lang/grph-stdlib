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

struct {
    // as all reference types
    struct typetable *isa;
    
    // the size of the window, in pixels
    grph_pos_t size;
    // the background paint of the window
    struct grph_existential paint;
} typedef grph_Background_t;

grph_Background_t *grphc_Background(grph_pos_t size, struct grph_existential *paint);

#endif /* GRPH_SHAPES_H */
