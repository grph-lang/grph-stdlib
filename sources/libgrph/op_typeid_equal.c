//
//  op_equal.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 19/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "existentials.h"
#include "grph_types.h"
#include "grph_string_t.h"

#include <stdlib.h>
#include <stdio.h>

size_t grphop_typeid_len(typeid_t type)
{
    int len;

    switch ((existential_type_id_t) type[0]) {
    case 0 ... EXISTENTIAL_ID_reference:
        return 1;
    case EXISTENTIAL_ID_optional:
    case EXISTENTIAL_ID_array:
        return 1 + grphop_typeid_len(type + 1);
    case EXISTENTIAL_ID_tuple:
    case EXISTENTIAL_ID_multi_or:
        len = 2;
        for (int n = 0; n < type[1]; n++) {
            len += grphop_typeid_len(type + len);
        }
        return len;
    case EXISTENTIAL_ID_mixed:
        return 1;
    }
}
