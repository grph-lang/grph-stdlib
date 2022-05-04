//
//  conversion_integer.c
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
#include <errno.h>

grph_integer_t float_to_integer(grph_float_t number)
{
    return (grph_integer_t) number;
}

static optional_integer_t strtoll_chk(grph_string_t *str, int base, int offset, int multiplier)
{
    bool need_free;
    char *data = grph_to_cstring(str, &need_free);
    char *out;
    errno = 0;
    grph_integer_t result = strtoll(data + offset, &out, base);
    if (need_free)
        free(data);
    if (errno || *out) {
        return (optional_integer_t) GRPH_NULL;
    } else {
        return (optional_integer_t) { true, multiplier * result };
    }
}

optional_integer_t string_to_integer(grph_string_t str)
{
    grph_integer_t len = grph_string_get_length(str);
    char *data = grph_string_get_data(&str);
    int offset = 0;
    int multiplier = 1;
    if (len == 0)
        return (optional_integer_t) GRPH_NULL;
    while (data[offset] == '+' || data[offset] == '-') {
        if (data[offset] == '-')
            multiplier *= -1;
        offset++;
        if (offset == len)
            return (optional_integer_t) GRPH_NULL;
    }
    if (len - offset >= 2 && data[offset] == '0') {
        switch (data[offset + 1]) {
        case 'x':
        case 'X':
            return strtoll_chk(&str, 16, offset + 2, multiplier);
        case 'o':
            return strtoll_chk(&str, 8, offset + 2, multiplier);
        case 'b':
            return strtoll_chk(&str, 2, offset + 2, multiplier);
        case 'z':
            return strtoll_chk(&str, 36, offset + 2, multiplier);
        }
    } else if (data[offset] == '#') {
        return strtoll_chk(&str, 16, offset + 1, multiplier);
    }
    return strtoll_chk(&str, 10, offset, multiplier);
}
