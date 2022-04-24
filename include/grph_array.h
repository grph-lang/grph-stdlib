//
//  grph_array.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 26/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef grph_array_h
#define grph_array_h

#include "grph_types.h"

struct {
    // as all reference types
    struct typetable *isa;
    
    // number of elements
    grph_integer_t count;
    // number of elements we can hold before realloc
    grph_integer_t capacity;
    // the buffer with all our elements
    void *buffer;
} typedef grph_array_t;


/// Allocate a new array
/// @param type the type of the array. must be an array type
/// @param capacity the initial capacity (should be a power of 2, will never actually be under 16)
grph_array_t *grpharr_create(struct typetable *type, grph_integer_t capacity);

/// Ensures the capacity of an array is at least the given value
/// @param array the array
/// @param capacity the minimum needed capacity
void grpharr_ensure_capacity(grph_array_t *array, grph_integer_t capacity);

/// Appends an element at the end of the array
/// Implements `array{+} = elem`
/// @param array the array
/// @param elem a pointer to the element to add
void grpharr_append(grph_array_t *array, void *elem);

/// Removes an element at the end of the array
/// Implements `elem = array{-}`
/// @param array the array
/// @param elem_out a pointer to where to put the removed element
void grpharr_pop(grph_array_t *array, void *elem_out);

/// Inserts an element at the given index
/// Implements `array{index+} = elem`
/// @param array the array
/// @param index the index where the element will be inserted
/// @param elem a pointer to the element to insert
void grpharr_insert(grph_array_t *array, grph_integer_t index, void *elem);

/// Replaces the element of the given index
/// Implements `array{index} = elem`
/// @param array the array
/// @param index the index where the element will be changed
/// @param elem a pointer to the new element
void grpharr_set(grph_array_t *array, grph_integer_t index, void *elem);

/// Removes the element at the given index
/// Implements `elem = array{index-}`
/// @param array the array
/// @param index the index where the element will be removed
/// @param elem_out a pointer to where to put the removed element
void grpharr_remove(grph_array_t *array, grph_integer_t index, void *elem_out);

/// Retrieves a value in an array
/// Implements `elem = array{index}`  
/// @param array the array
/// @param index the index to retrieve
/// @param elem_out a pointer to where to put the element 
void grpharr_get(grph_array_t *array, grph_integer_t index, void *elem_out);

#endif /* grph_array_h */
