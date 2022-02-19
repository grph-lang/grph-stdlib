//
//  existentials.inc
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 14/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

// This file is meant to be included by headers, the macros must be defined beforehand

PRIMITIVE_TYPEID(0, void)
PRIMITIVE_TYPEID(1, boolean)
PRIMITIVE_TYPEID(2, integer)
PRIMITIVE_TYPEID(3, float)
PRIMITIVE_TYPEID(4, rotation)
PRIMITIVE_TYPEID(5, pos)
PRIMITIVE_TYPEID(6, string)

SPECIAL_TYPEID(100, reference)

SPECIAL_TYPEID(128, tuple)
SPECIAL_TYPEID(129, array)
SPECIAL_TYPEID(130, optional)
//SPECIAL_TYPEID(131, funcref)

// These existentials EXIDs may not appear as the first component of an existential
// They are valid in nested existentials though (ex: mixed?)

/// Note: num is defined as integer|float, paint is color|linear|radial
SPECIAL_TYPEID(254, multi_or)
SPECIAL_TYPEID(255, mixed)
