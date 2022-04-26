//
//  vwt.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 23/04/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "vwt.h"
#include "grph_types.h"
#include "grph_string_t.h"
#include "box.h"

#include <string.h>

void grphvwt_copy_trivial(void *restrict dest, void *restrict src, struct typetable *restrict type)
{
    memcpy(dest, src, type->vwt->instance_size);
}

void grphvwt_destroy_trivial(void *restrict value, struct typetable *restrict type)
{
    (void) value, (void) type;
}

void grphvwt_copy_mixed(void *restrict dest, void *restrict src, struct typetable *restrict type)
{
    (void) type;
    struct grph_existential *to = dest;
    struct grph_existential *from = src;
    
    // TODO: handle larger values
    to->type = from->type;
    from->type->vwt->copy(&to->data, &from->data, from->type);
}

void grphvwt_destroy_mixed(void *restrict value, struct typetable *restrict type)
{
    (void) type;
    struct grph_existential *val = value;
    
    // TODO: handle larger values
    val->type->vwt->destroy(&val->data, val->type);
}

void grphvwt_retain_string(void *restrict dest, void *restrict src, struct typetable *restrict type)
{
    grph_string_t *str = src;
    memcpy(dest, src, type->vwt->instance_size);
    if (!grph_string_is_immortal(*str) && !grph_string_is_small(*str))
        retain_box(str->buffer);
}

void grphvwt_release_string(void *restrict value, struct typetable *restrict type)
{
    (void) type;
    grph_string_t *str = value;
    
    if (!grph_string_is_immortal(*str) && !grph_string_is_small(*str)) {
        if (release_box(str->buffer)) {
            dealloc_box(str->buffer);
        }
    }
}

void grphvwt_retain_ref(void *restrict dest, void *restrict src, struct typetable *restrict type)
{
    memcpy(dest, src, type->vwt->instance_size);
    retain_box(*(void **) src);
}

void grphvwt_release_ref(void *restrict _value, struct typetable *restrict _type)
{
    (void) _type;
    // _value is a pointer to the ref, value is the ref
    void *value = *(void **) _value;
    // retrieve real type from isa, first element in value
    struct typetable *type = *(void **) value;
    
    if (type->vwt->destroy != &grphvwt_release_ref) {
        // call the actual type's destructor
        return type->vwt->destroy(_value, type);
    }
    if (release_box(value)) {
        dealloc_box(value);
    }
}

void grphvwt_copy_optional(void *restrict dest, void *restrict src, struct typetable *restrict type)
{
    struct typetable *elemty = type->generics[0];
    bool *exists = src;
    void *content = src + elemty->vwt->alignment;
    
    if (*exists) {
        bool *exists_dest = dest;
        *exists_dest = true;
        elemty->vwt->copy(dest + elemty->vwt->alignment, content, elemty);
    } else {
        // trivial
        memcpy(dest, src, type->vwt->instance_size);
    }
}

void grphvwt_destroy_optional(void *restrict value, struct typetable *restrict type)
{
    struct typetable *elemty = type->generics[0];
    bool *exists = value;
    void *content = value + elemty->vwt->alignment;
    
    if (*exists) {
        elemty->vwt->destroy(content, elemty);
    } // else trivial
}

void grphvwt_copy_tuple(void *restrict dest, void *restrict src, struct typetable *restrict type)
{
    int i = 0;
    size_t offset = 0;
    
    while (type->generics[i]) {
        while (i != 0 && (offset & (type->generics[i]->vwt->alignment - 1)))
            offset++;
        type->generics[i]->vwt->copy(dest + offset, src + offset, type->generics[i]);
        offset += type->generics[i]->vwt->instance_size;
        i++;
    }
}

void grphvwt_destroy_tuple(void *restrict value, struct typetable *restrict type)
{
    int i = 0;
    size_t offset = 0;
    
    while (type->generics[i]) {
        while (i != 0 && (offset & (type->generics[i]->vwt->alignment - 1)))
            offset++;
        type->generics[i]->vwt->destroy(value + offset, type->generics[i]);
        offset += type->generics[i]->vwt->instance_size;
        i++;
    }
}
