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

#include "grph_types.h"
#include "grph_string_t.h"
#include "grph_op.h"
#include "existentials.h"
#include "typetable.h"
#include "grph_array.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

grph_string_t int_to_string(grph_integer_t number)
{
    char *box = malloc(21); // max size is 20 + \0
    grph_integer_t len = sprintf(box, "%lld", number);
    return (grph_string_t) { (0b010ULL << 61) | len, box };
}

grph_string_t float_to_string(grph_float_t number)
{
    char *box = malloc(32); // idk, swift uses 32 bytes
    grph_integer_t len = snprintf(box, 32, "%f", number);
    return (grph_string_t) { (0b010ULL << 61) | len, box };
}

grph_string_t grphas_string_forced(struct grph_existential *val);

grph_integer_t mixed_array_length(struct grph_existential *value)
{
    grph_array_t *array = value->data[0];
    
    return array->count;
}

grph_string_t mixed_array_elem_to_string(struct grph_existential *value, int index)
{
    grph_array_t *array = value->data[0];
    struct typetable *elemty = array->isa->generics[0];
    size_t elemsize = elemty->vwt->instance_size;
    void *elem = alloca(elemsize);

    grpharr_get(value->data[0], index, elem);
    if (TYPE_IS_EXISTENTIAL(elemty))
        return grphas_string_forced(elem);
    struct grph_existential ext;
    ext.type = elemty;
    if (elemsize > sizeof(value->data)) {
        // TODO: box should be refcounted
        ext.data[0] = &elem;
    } else {
        memcpy(&ext.data, elem, elemsize);
    }
    return grphas_string_forced(&ext);
}

bool mixed_is_array(struct grph_existential *value)
{
    return TYPETABLE_TYPEID_CHAR(value->type) == EXISTENTIAL_ID_array;
}

struct typetable *mixed_array_elem_type(struct grph_existential *value)
{
    grph_array_t *array = value->data[0];
    return array->isa->generics[0];
}

grph_string_t type_to_string(struct typetable *type)
{
    return (grph_string_t) { STRING_IMMORTAL | STRING_NIL_TERMINATED | strlen(type->type_name), type->type_name };
}

grph_string_t grphop_concat_strings(grph_string_t lhs, grph_string_t rhs)
{
    char const *lhs_data = grph_string_get_data(&lhs);
    char const *rhs_data = grph_string_get_data(&rhs);
    int64_t lhs_len = grph_string_get_length(lhs);
    int64_t rhs_len = grph_string_get_length(rhs);
    
    int64_t total_len = lhs_len + rhs_len;
    char *box = malloc(total_len + 1);
    memcpy(box, lhs_data, lhs_len);
    memcpy(box + lhs_len, rhs_data, rhs_len);
    box[total_len] = 0;
    return (grph_string_t) { (0b010ULL << 61) | total_len, box };
}
