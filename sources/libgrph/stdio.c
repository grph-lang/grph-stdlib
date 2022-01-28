//
//  stdio.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 27/01/2022.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "ns/stdio.h"
#include "grph_types.h"

#include <unistd.h>

void grph_stdio_printOut(grph_string_t message)
{
    write(1, message.buffer, STR_LEN(message));
}

void grph_stdio_printError(grph_string_t message)
{
    write(2, message.buffer, STR_LEN(message));
}
