//
//  grph_types.h
//  GRPH Standard Library
//
//  Created by Emil Pedersen on 26/01/2022.
//

#ifndef grph_types_h
#define grph_types_h

#include <inttypes.h>

typedef int64_t grph_int_t;
typedef double grph_float_t;
typedef float grph_rotation_t;
typedef char grph_boolean_t;

struct {
    grph_float_t x;
    grph_float_t y;
} typedef grph_pos_t;

#endif /* grph_types_h */
