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

// This file is meant to be included by other source files, the macros must be defined beforehand

SWT_FIELD(location, grph_pos_t)
SWT_FIELD(zPos, grph_integer_t)
SWT_FIELD(size, grph_pos_t)
SWT_FIELD(rotation, grph_rotation_t)
SWT_FIELD(paint, struct grph_existential)
SWT_FIELD(strokeWrapper, struct stroke_wrapper)
