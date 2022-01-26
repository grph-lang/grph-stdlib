//
//  standard.c
//  libgrph
//
//  Created by Emil Pedersen on 26/01/2022.
//

#include "grph_types.h"

#include <unistd.h>
#include <stdlib.h>

void grph_standard_wait(grph_int_t time)
{
    usleep(time * 1000);
}

void grph_standard_end(void)
{
    exit(0);
}
