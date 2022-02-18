//
//  test_stringContains.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 16/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "ns/strutils.h"
#include "grph_string_t.h"

#include <criterion/criterion.h>

Test(charToInteger, simple)
{
    cr_assert_eq(grph_strutils_charToInteger(grph_string_literal("k")), 'k');
    cr_assert_eq(grph_strutils_charToInteger(grph_string_literal("4")), '4');
}

Test(integerToChar, simple)
{
    grph_string_t str = grph_strutils_integerToChar('k');
    
    cr_assert_eq(grph_string_get_length(str), 1);
    cr_assert_str_eq(grph_string_get_data(&str), "k");
}

Test(integerToChar, compat)
{
    cr_assert_eq(grph_strutils_charToInteger(grph_strutils_integerToChar('4')), '4');
}
