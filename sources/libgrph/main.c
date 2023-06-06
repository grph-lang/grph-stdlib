//
//  main.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 27/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_array.h"
#include "typetable.h"

#include <string.h>

// defined in user code
void grph_entrypoint(void);

// defined in graphic library, if linking against it
void grphg_init(void) __attribute__((weak));

struct typetable *return_string_array_typetable(void);

grph_array_t *grphv_global_argv;

int main(int argc, char **argv)
{
    grph_array_t *args = grpharr_create(return_string_array_typetable(), argc);
    for (int i = 0; i < argc; i++) {
        grph_string_t converted = { (0b110ULL << 61) | strlen(argv[i]), argv[i] };
        grpharr_append(args, &converted);
    }
    grphv_global_argv = args;
    if (grphg_init)
        grphg_init();
    grph_entrypoint();
    grphv_global_argv->isa->vwt->destroy(&grphv_global_argv, grphv_global_argv->isa);
}
