//
//  typetable.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 26/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef typetable_h
#define typetable_h

#include <stdint.h>

#ifdef __cplusplus
    #define restrict __restrict__
#endif

struct typetable;
typedef void copy_func(void *restrict dest, void *restrict src, struct typetable *restrict type);
typedef void destroy_func(
    void * restrict value, struct typetable * restrict type);
typedef void deinit_func(void *value);

struct vwt {
    /// The size of an instance of this type
    uint64_t instance_size;
    uint64_t alignment;
    copy_func *copy;
    destroy_func *destroy;
    deinit_func *deinit;
};

struct typetable {
    /// A pointer to the nil terminated name of the specialized type
    /// the precedent char, `tt.type_name[-1]`, is the typeid char
    char *type_name;
    /// The value witness table for this type, with extra information
    struct vwt *vwt;
    // Add more fields here, including the vwt
    /// The generics vector, inline, null terminated
    struct typetable *generics[0];
};

#define TYPETABLE_TYPEID_CHAR(tt) ((typeid_t) (tt)->type_name[-1])
#define TYPE_IS_EXISTENTIAL(tt) (TYPETABLE_TYPEID_CHAR(tt) == EXISTENTIAL_ID_mixed || TYPETABLE_TYPEID_CHAR(tt) == EXISTENTIAL_ID_multi_or_ext)

#endif /* typetable_h */
