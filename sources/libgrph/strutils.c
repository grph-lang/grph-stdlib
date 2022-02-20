//
//  strutils.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 27/01/2022.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "ns/strutils.h"

#include "grph_types.h"
#include "grph_string_t.h"

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool starts_with(char const *haystack, char const *needle, grph_integer_t size)
{
    for (int i = 0; i < size; i++) {
        if (haystack[i] != needle[i])
            return false;
    }
    return true;
}

grph_integer_t grph_strutils_indexInString(grph_string_t string, grph_string_t substring)
{
    char const *string_data = grph_string_get_data(&string);
    char const *substr_data = grph_string_get_data(&substring);
    uint64_t string_len = grph_string_get_length(string);
    uint64_t substr_len = grph_string_get_length(substring);
    grph_integer_t checkable = string_len - substr_len;
    
    for (grph_integer_t i = 0; i <= checkable; i++) {
        if (starts_with(string_data + i, substr_data, substr_len)) {
            return i;
        }
    }
    return -1;
}

grph_integer_t grph_strutils_lastIndexInString(grph_string_t string, grph_string_t substring)
{
    char const *string_data = grph_string_get_data(&string);
    char const *substr_data = grph_string_get_data(&substring);
    uint64_t string_len = grph_string_get_length(string);
    uint64_t substr_len = grph_string_get_length(substring);
    grph_integer_t checkable = string_len - substr_len;
    
    for (grph_integer_t i = checkable; i >= 0; i--) {
        if (starts_with(string_data + i, substr_data, substr_len)) {
            return i;
        }
    }
    return -1;
}

grph_boolean_t grph_strutils_stringContains(grph_string_t string, grph_string_t substring)
{
    return grph_strutils_indexInString(string, substring) >= 0;
}

grph_string_t grph_strutils_substring(grph_string_t string, grph_integer_t start, grph_integer_t end)
{
    if (start > end)
        abort(); // TODO: throw
    if (start == 0) {
        // increase refcount
        return (grph_string_t) { ((0b111ULL << 61) & string.metadata) | end, string.buffer };
    }
    char *data = grph_string_get_data(&string);
    if (end - start <= 8) {
        uintptr_t result = 0;
        for (int i = 0; i < end - start; i++) {
            result |= (uintptr_t) data[start + i] << (i * 8);
        }
        return (grph_string_t) { (0b101ULL << 61) | ((end - start < 8) ? (0b010ULL << 61) : 0) | (end - start), (void *) result };
    }
    char *cpy = malloc(end - start + 1);
    memcpy(cpy, data + start, end - start);
    cpy[end - start] = 0;
    return (grph_string_t) { (0b010ULL << 61) | (end - start), cpy };
}

grph_integer_t grph_strutils_charToInteger(grph_string_t character)
{
    // TODO: throw if len == 0
    return grph_string_get_data(&character)[0];
}

// we only handle ascii
grph_string_t grph_strutils_integerToChar(grph_integer_t codePoint)
{
    return (grph_string_t) { (0b111ULL << 61) | 1, (void *) codePoint };
}
