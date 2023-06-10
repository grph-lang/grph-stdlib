//
//  fields.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 12/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_fields.h"
#include "grph_types.h"
#include "grph_string_t.h"
#include "typetable.h"
#include "existentials.h"

#include <stdio.h>

grph_integer_t grphp_string_length_get(grph_string_t this)
{
    return grph_string_get_length(this);
}

static bool type_is_ref(struct typetable *tt)
{
    return ((TYPETABLE_TYPEID_CHAR(tt) >= 64 && TYPETABLE_TYPEID_CHAR(tt) < 128)
            || TYPETABLE_TYPEID_CHAR(tt) == EXISTENTIAL_ID_array
            || TYPETABLE_TYPEID_CHAR(tt) == EXISTENTIAL_ID_multi_or_ref);
}

struct typetable *grphp_mixed_type_get(struct grph_existential *this)
{
    struct typetable *easy = this->type;

    if (type_is_ref(easy)) {
        return *(struct typetable **) this->data[0];
    }
    return easy;
}
