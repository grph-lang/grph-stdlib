//
//  grph_types.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 26/01/2022.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef GRPH_STRING_T_H
#define GRPH_STRING_T_H

#include "grph_types.h"

#include <stdbool.h>

/// Returns true if the string is immortal, false otherwise.
/// An immortal string cannot be freed, and as such is not boxed:
/// it is stored in a readonly static segment.
/// String literals and string literal substrings are immortal.
/// All small strings are also immortal.
/// @param str the string
static inline bool grph_string_is_immortal(grph_string_t str)
{
    return str.metadata & (0b100ULL << 61);
}

/// Returns true if it is valid to read str[str.length], and that it will yield a NUL byte
/// If it returns false, it is illegal to read past the end of the string.
/// Used to optimize some C interop.
/// @param str the string
static inline bool grph_string_is_nil_terminated(grph_string_t str)
{
    return str.metadata & (0b010ULL << 61);
}

/// Returns true if the string is so small it is stored inside the pointer.
/// If true, the buffer stores at most 8 bytes of characters.
/// If false, the buffer is a pointer to a box containing the characters (unless immortal).
/// @param str the string
static inline bool grph_string_is_small(grph_string_t str)
{
    return str.metadata & (0b001ULL << 61);
}

/// Returns the length of a string
/// @param str the string
static inline uint64_t grph_string_get_length(grph_string_t str)
{
    return str.metadata & ~(0b111ULL << 61);
}

/// Returns a pointer to the string buffer.
/// @discussion It is not allowed to read past the end of the string (unless grph_string_is_nil_terminated returns true)
/// You may only read the number of bytes returned by `grph_string_get_length`.
/// @remark The returned pointer's lifetime is tied to the given pointer's lifetime.
/// @param str a pointer to the string
static inline char *grph_string_get_data(grph_string_t *str)
{
    if (grph_string_is_small(*str))
        return (char *) &str->buffer;
    return str->buffer; // assume immortal, boxes aren't implemented
}


/// Converts a GRPH string to a nil-terminated C string
/// @param str the GRPH string
/// @param freeable out-only variable, true if you must free the result, false otherwise
char *grph_to_cstring(grph_string_t *str, bool *freeable);

/// Creates a GRPH string
static inline grph_string_t grph_string_literal(char *str, unsigned long long len)
{
    return (grph_string_t) { (0b110ULL << 61) | len, str };
}

#define grph_string_literal(str) grph_string_literal(str, sizeof(str) - 1)

#endif /* GRPH_STRING_T_H */
