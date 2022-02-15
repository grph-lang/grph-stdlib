//
//  existentials.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 14/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef EXISTENTIALS_H
#define EXISTENTIALS_H

#define PRIMITIVE_TYPEID(id, name) \
    EXISTENTIAL_ID_##name = id,

typedef enum : unsigned char {
    #include "existentials.inc"
} existential_type_id_t;

#endif /* EXISTENTIALS_H */
