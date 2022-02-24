//
//  standard.h
//  GRPH stdlib - libgrph
//
//  Autogenerated by `grph gen-header standard`.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef GRPH_NS_STANDARD_H
#define GRPH_NS_STANDARD_H

#include "grph_types.h"

optional_integer_t grph_standard_stringToInteger(grph_string_t string);
optional_float_t grph_standard_stringToFloat(grph_string_t string);
grph_float_t grph_standard_getXForPos(grph_pos_t pos);
grph_float_t grph_standard_getYForPos(grph_pos_t pos);
grph_rotation_t grph_standard_integerToRotation(grph_integer_t integer);
grph_integer_t grph_standard_rotationToInteger(grph_rotation_t rotation);
grph_integer_t grph_standard_getNumberOfShapes(void);
void grph_standard_validateAll(void);
void grph_standard_update(void);
void grph_standard_wait(grph_integer_t time);
void grph_standard_end(void);

#endif /* GRPH_NS_STANDARD_H */

