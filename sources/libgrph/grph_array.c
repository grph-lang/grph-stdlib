//
//  grph_array.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 26/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_array.h"
#include "existentials.h"
#include "typetable.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

grph_array_t *grpharr_create(struct typetable *type, grph_integer_t capacity)
{
    grph_array_t *box = malloc(sizeof(grph_array_t));
    
    box->box_refcount = 0;
    box->isa = type;
    box->count = 0;
    box->capacity = capacity > 16 ? capacity : 16;
    box->buffer = malloc(box->capacity * type->generics[0]->vwt->instance_size);
    return box;
}

// not thread safe
void grpharr_ensure_capacity(grph_array_t *array, grph_integer_t capacity)
{
    if (array->capacity < capacity) {
        grph_integer_t ideal_cap = array->capacity * 2;
        array->capacity = capacity > ideal_cap ? capacity : ideal_cap;
        array->buffer = realloc(array->buffer, array->capacity * array->isa->generics[0]->vwt->instance_size);
    }
}

// array{+} = elem
void grpharr_append(grph_array_t *array, void *elem)
{
    grph_integer_t elemsize = array->isa->generics[0]->vwt->instance_size;
    
    grpharr_ensure_capacity(array, array->count + 1);
    memcpy(array->buffer + elemsize * array->count, elem, elemsize);
    array->count++;
}

// elem = array{-}
void grpharr_pop(grph_array_t *array, void *elem_out)
{
    grph_integer_t elemsize = array->isa->generics[0]->vwt->instance_size;
    
    memcpy(elem_out, array->buffer + elemsize * array->count, elemsize);
    array->count--;
}

// array{index+} = elem
void grpharr_insert(grph_array_t *array, grph_integer_t index, void *elem)
{
    grph_integer_t elemsize = array->isa->generics[0]->vwt->instance_size;
    grph_integer_t offset = index * elemsize;
    
    grpharr_ensure_capacity(array, array->count + 1);
    memmove(array->buffer + offset + elemsize, array->buffer + offset, elemsize * array->count - offset);
    memcpy(array->buffer + offset, elem, elemsize);
    array->count++;
}

// array{index} = elem
void grpharr_set(grph_array_t *array, grph_integer_t index, void *elem)
{
    grph_integer_t elemsize = array->isa->generics[0]->vwt->instance_size;
    grph_integer_t offset = index * elemsize;
    
    // TODO: release previous value
    memcpy(array->buffer + offset, elem, elemsize);
}

// elem = array{index-}
void grpharr_remove(grph_array_t *array, grph_integer_t index, void *elem_out)
{
    grph_integer_t elemsize = array->isa->generics[0]->vwt->instance_size;
    grph_integer_t offset = index * elemsize;
    
    memcpy(elem_out, array->buffer + offset, elemsize);
    memmove(array->buffer + offset, array->buffer + offset + elemsize, elemsize * (array->count - 1) - offset);
    array->count--;
}

// elem = array{index}
void grpharr_get(grph_array_t *array, grph_integer_t index, void *elem_out)
{
    grph_integer_t elemsize = array->isa->generics[0]->vwt->instance_size;
    grph_integer_t offset = index * elemsize;
    
    memcpy(elem_out, array->buffer + offset, elemsize);
}

// mixed elem = array{index} for array conversion thunks
void grpharr_get_mixed(grph_array_t *array, grph_integer_t index, void *elem_out)
{
    struct typetable *elem = array->isa->generics[0];
    size_t elemsize = elem->vwt->instance_size;
    void *src = array->buffer + index * elemsize;
    struct grph_existential *dest = elem_out;
    
    if (TYPETABLE_TYPEID_CHAR(elem) == EXISTENTIAL_ID_mixed) {
        memcpy(dest, src, elemsize);
        return;
    }
    dest->type = elem;
    if (elemsize > sizeof(dest->data)) {
        // TODO: box should be refcounted
        void *copy = malloc(elemsize);
        memcpy(copy, src, elemsize);
        dest->data[0] = copy;
    } else {
        memcpy(dest->data, src, elemsize);
    }
}
