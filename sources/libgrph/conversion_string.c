//
//  conversion_string.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 14/02/2022.
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

static grph_string_t int_to_string(grph_integer_t number)
{
    char *box = malloc(21); // max size is 20 + \0
    grph_integer_t len = sprintf(box, "%lld", number);
    return (grph_string_t) { (0b010ULL << 61) | len, box };
}

static grph_string_t float_to_string(grph_float_t number)
{
    char *box = malloc(32); // idk, swift uses 32 bytes
    grph_integer_t len = snprintf(box, 32, "%f", number);
    return (grph_string_t) { (0b010ULL << 61) | len, box };
}

// because of stupid ABI stuff, if expecting a struct, it will be passed by pointer instead of being unpacked
grph_string_t grphas_string(typeid val_type, void *val_data0, void *val_data1, void *val_data2)
{
    struct grph_existential val = { val_type, { val_data0, val_data1, val_data2} };
    switch ((existential_type_id_t) *val.type) {
    case EXISTENTIAL_ID_void:
        return grph_string_literal("void.VOID");
    case EXISTENTIAL_ID_boolean:
        return val.data[0] ? grph_string_literal("true") : grph_string_literal("false");
    case EXISTENTIAL_ID_integer:
        return int_to_string(*(grph_integer_t *) &val.data[0]);
    case EXISTENTIAL_ID_float:
        return float_to_string(*(grph_float_t *) &val.data[0]);
    case EXISTENTIAL_ID_string:
        return *(grph_string_t *) &val.data[0];
    }
    return grph_string_literal("<?invalid?>");
}
