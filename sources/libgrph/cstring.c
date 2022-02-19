//
//  cstring.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 19/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_types.h"
#include "grph_string_t.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *grph_to_cstring(grph_string_t *str, bool *freeable)
{
    if (grph_string_is_nil_terminated(*str)) {
        *freeable = false;
        return grph_string_get_data(str);
    } else {
        grph_integer_t len = grph_string_get_length(*str);
        char *src = grph_string_get_data(str);
        char *copy = malloc(len + 1);
        memcpy(copy, src, len);
        copy[len] = 0;
        *freeable = true;
        return copy;
    }
}
