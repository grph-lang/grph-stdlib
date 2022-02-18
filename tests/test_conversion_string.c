//
//  test_conversion_string.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 18/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "ns/strutils.h"
#include "grph_string_t.h"
#include "existentials.h"

#include <criterion/criterion.h>

#include <limits.h>

grph_string_t grphas_string(typeid_t type, void *data0, void *data1, void *data2);

Test(as_string, integer)
{
    unsigned char id = EXISTENTIAL_ID_integer;
    grph_string_t result = grphas_string(&id, (void *) 42, NULL, NULL);
    cr_assert_eq(grph_string_get_length(result), 2);
    cr_assert_str_eq(grph_string_get_data(&result), "42");
}

Test(as_string, integer_max)
{
    unsigned char id = EXISTENTIAL_ID_integer;
    grph_string_t result = grphas_string(&id, (void *) LLONG_MAX, NULL, NULL);
    cr_assert_eq(grph_string_get_length(result), 19);
    cr_assert_str_eq(grph_string_get_data(&result), "9223372036854775807");
}

Test(as_string, integer_min)
{
    unsigned char id = EXISTENTIAL_ID_integer;
    grph_string_t result = grphas_string(&id, (void *) LLONG_MIN, NULL, NULL);
    cr_assert_eq(grph_string_get_length(result), 20);
    cr_assert_str_eq(grph_string_get_data(&result), "-9223372036854775808");
}

Test(as_string, float)
{
    unsigned char id = EXISTENTIAL_ID_float;
    double d = 12.125;
    grph_string_t result = grphas_string(&id, *(void **) &d, NULL, NULL);
    cr_assert_eq(grph_string_get_length(result), 9);
    cr_assert_str_eq(grph_string_get_data(&result), "12.125000");
}

Test(as_string, boolean_true)
{
    unsigned char id = EXISTENTIAL_ID_boolean;
    grph_string_t result = grphas_string(&id, (void *) -1, NULL, NULL);
    cr_assert_eq(grph_string_get_length(result), 4);
    cr_assert_str_eq(grph_string_get_data(&result), "true");
}

Test(as_string, boolean_false)
{
    unsigned char id = EXISTENTIAL_ID_boolean;
    grph_string_t result = grphas_string(&id, (void *) 0, NULL, NULL);
    cr_assert_eq(grph_string_get_length(result), 5);
    cr_assert_str_eq(grph_string_get_data(&result), "false");
}

Test(as_string, void)
{
    unsigned char id = EXISTENTIAL_ID_void;
    grph_string_t result = grphas_string(&id, NULL, NULL, NULL);
    cr_assert_eq(grph_string_get_length(result), 9);
    cr_assert_str_eq(grph_string_get_data(&result), "void.VOID");
}

Test(as_string, string)
{
    unsigned char id = EXISTENTIAL_ID_string;
    grph_string_t original = grph_string_literal("Wow!");
    grph_string_t result = grphas_string(&id, (void *) original.metadata, original.buffer, NULL);
    cr_assert_eq(grph_string_get_length(result), 4);
    cr_assert_str_eq(grph_string_get_data(&result), grph_string_get_data(&original));
}

