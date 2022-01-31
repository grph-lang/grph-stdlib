//
//  test_strings.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 31/01/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_string_t.h"

#include <criterion/criterion.h>

Test(strings, literal)
{
    grph_string_t str = { (0b110ULL << 61) | 13, "Hello, world!" };
    
    cr_assert_eq(grph_string_get_length(str), 13);
    cr_assert(grph_string_is_immortal(str));
    cr_assert_str_eq(grph_string_get_data(&str), "Hello, world!");
}

Test(strings, small_single_char)
{
    grph_string_t str = { (0b101ULL << 61) | 1, (void *) 'a' };
    
    cr_assert_eq(grph_string_get_length(str), 1);
    cr_assert_eq(grph_string_get_data(&str)[0], 'a');
}

Test(strings, small8)
{
    // assume big endian
    grph_string_t str = { (0b101ULL << 61) | 8, (void *) 0x42494C2048505247ULL };
    
    cr_assert_eq(grph_string_get_length(str), 8);
    cr_assert_arr_eq(grph_string_get_data(&str), "GRPH LIB", 8);
}
