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

// Structs

PRIMITIVE_TYPEID(0, void)
PRIMITIVE_TYPEID(1, boolean)
PRIMITIVE_TYPEID(2, integer)
PRIMITIVE_TYPEID(3, float)
PRIMITIVE_TYPEID(4, rotation)
PRIMITIVE_TYPEID(5, pos)
PRIMITIVE_TYPEID(6, string)

PRIMITIVE_TYPEID(7, color)
PRIMITIVE_TYPEID(8, linear)
PRIMITIVE_TYPEID(9, radial)

PRIMITIVE_TYPEID(10, direction)
PRIMITIVE_TYPEID(11, stroke)

PRIMITIVE_TYPEID(12, font)
PRIMITIVE_TYPEID(13, type)

// References

PRIMITIVE_TYPEID(64, Background)
PRIMITIVE_TYPEID(65, Rectangle)
PRIMITIVE_TYPEID(66, Circle)
PRIMITIVE_TYPEID(67, Line)
PRIMITIVE_TYPEID(68, Polygon)
PRIMITIVE_TYPEID(69, Text)
PRIMITIVE_TYPEID(70, Path)
PRIMITIVE_TYPEID(71, Group)

// Generics

SPECIAL_TYPEID(128, tuple)
SPECIAL_TYPEID(129, array)
SPECIAL_TYPEID(130, optional)
SPECIAL_TYPEID(131, funcref)

// These cannot be instanciated, but they can appear as generics or at the right hand side of a cast
// They are valid in nested existentials though (ex: mixed?)

/// Note: num is defined as float|integer, paint is color|linear|radial
SPECIAL_TYPEID(254, multi_or)
SPECIAL_TYPEID(255, mixed)
