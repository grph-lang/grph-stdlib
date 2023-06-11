//
//  shape_witness.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 10/06/2023.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef GRPH_SHAPE_WITNESS_H
#define GRPH_SHAPE_WITNESS_H

#include <stdint.h>

struct shape_witness_table {
#define SWT_FIELD(name, type) uint16_t name##_offset;
#include "shape_witness.inc"
#undef SWT_FIELD
};

#endif /* GRPH_SHAPE_WITNESS_H */
