//
//  grph_op.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 19/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef GRPH_OP_H
#define GRPH_OP_H

#include "grph_types.h"
#include <stddef.h>

size_t grphop_typeid_len(typeid_t type);
grph_boolean_t grphop_typeid_equal(typeid_t lhs, typeid_t rhs);

#endif /* GRPH_OP_H */
