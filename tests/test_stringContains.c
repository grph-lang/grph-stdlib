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

Test(stringContains, simple)
{
    grph_string_t str = grph_string_literal("abc");
    cr_assert(grph_strutils_stringContains(str, grph_string_literal("a")));
    cr_assert(grph_strutils_stringContains(str, grph_string_literal("b")));
    cr_assert(grph_strutils_stringContains(str, grph_string_literal("c")));
    cr_assert_not(grph_strutils_stringContains(str, grph_string_literal("d")));
    cr_assert_not(grph_strutils_stringContains(str, grph_string_literal("\0")));
}

Test(indexInString, simple)
{
    grph_string_t str = grph_string_literal("Hello it is a small world isn't it?");
    cr_assert_eq(grph_strutils_indexInString(str, grph_string_literal("it")), 6);
    cr_assert_eq(grph_strutils_lastIndexInString(str, grph_string_literal("it")), 32);
    cr_assert_eq(grph_strutils_indexInString(str, grph_string_literal("isn't")), 26);
    cr_assert_eq(grph_strutils_lastIndexInString(str, grph_string_literal("isn't")), 26);
    cr_assert_eq(grph_strutils_indexInString(str, grph_string_literal("hello")), -1);
    cr_assert_eq(grph_strutils_lastIndexInString(str, grph_string_literal("hello")), -1);
}

Test(indexInString, bigger_substr)
{
    grph_string_t str = grph_string_literal("Hello");
    grph_string_t substr = grph_string_literal("Hello it is a small world isn't it?");
    cr_assert_eq(grph_strutils_indexInString(str, substr), -1);
    cr_assert_eq(grph_strutils_lastIndexInString(str, substr), -1);
}
