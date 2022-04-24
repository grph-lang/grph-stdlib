//
//  box.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 23/04/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef box_h
#define box_h

#include <stddef.h>
#include <stdbool.h>

#define BOX_REFCOUNT(b) ((size_t *) b)[-1]

/// Allocates a box
void *alloc_box(size_t size) __attribute__((malloc));
/// Deallocates a box
void dealloc_box(void *box);

/// Increases the refcount of a box
void retain_box(void *box);
/// Decreases the refcount of a box, unless it was the last reference, in which case it returns true.
/// It is your responsibility to deallocate it.
bool release_box(void *box);

#endif /* box_h */
