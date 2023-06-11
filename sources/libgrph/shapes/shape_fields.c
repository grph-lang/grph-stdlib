//
//  shape_fields.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 11/06/2023.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_shapes.h"
#include "shape_witness.h"

#include <stddef.h>

#define SWT_FIELD(name, type) \
type grphp_shape_##name##_get(grph_shape_t *shape) \
{ \
    size_t offset = shape->isa->vwt->swt->name##_offset; \
    void *opaque = shape; \
    return *(type *) (opaque + offset); \
}
#define STROKE_WRAPPER_FIELD(name, type) \
type grphp_shape_##name##_get(grph_shape_t *shape) \
{ \
    return grphp_shape_strokeWrapper_get(shape).name; \
}
#include "shape_witness.inc"
#undef SWT_FIELD
