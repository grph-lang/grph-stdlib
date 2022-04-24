//
//  box.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 19/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "box.h"
#include "grph_types.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *alloc_box(size_t size)
{
    // register sized refcount to avoid most alignment issues (we dont use int128)
    size_t *box = malloc(size + sizeof(size_t));
#ifdef DEBUG_BOX
    fprintf(stderr, "%p: alloc\n", box + 1);
#endif
    box[0] = 0;
    return box + 1;
}

void dealloc_box(void *_box)
{
    size_t *box = _box;
#ifdef DEBUG_BOX
    fprintf(stderr, "%p: dealloc\n", box);
#endif
    free(box - 1);
}

void retain_box(void *box)
{
#ifdef DEBUG_BOX
    fprintf(stderr, "%p: retain\n", box);
#endif
    BOX_REFCOUNT(box)++;
}

bool release_box(void *box)
{
#ifdef DEBUG_BOX
    fprintf(stderr, "%p: release\n", box);
#endif
    if (BOX_REFCOUNT(box) == 0) {
        return true;
    } else {
        BOX_REFCOUNT(box)--;
        return false;
    }
}
