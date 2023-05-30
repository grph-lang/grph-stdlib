//
//  conversion_rotation.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 20/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_types.h"
#include "grph_string_t.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

grph_rotation_t integer_to_rotation(grph_integer_t number)
{
    return (grph_rotation_t) number;
}

grph_rotation_t float_to_rotation(grph_float_t number)
{
    return (grph_rotation_t) number;
}

optional_rotation_t string_to_rotation(grph_string_t str)
{
    bool need_free;
    char *data = grph_to_cstring(&str, &need_free);
    char *out;
    errno = 0;
    grph_rotation_t result = strtod(data, &out);
    if (need_free)
        free(data);
    if (errno || *out) {
        return (optional_rotation_t) GRPH_NULL;
    } else {
        return (optional_rotation_t) { true, result };
    }
}
