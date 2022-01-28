//
//  standard.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 26/01/2022.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "ns/standard.h"
#include "grph_types.h"

#include <unistd.h>
#include <stdlib.h>

void grph_standard_wait(grph_integer_t time)
{
    usleep(time * 1000);
}

void grph_standard_end(void)
{
    exit(0);
}
