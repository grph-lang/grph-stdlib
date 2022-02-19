//
//  test_op_typeid_equal.c
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 19/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#include "grph_op.h"
#include "existentials.h"

#include <criterion/criterion.h>

Test(typeid_equal, diff_len)
{
    unsigned char lhs[] = { EXISTENTIAL_ID_boolean };
    unsigned char rhs[] = { EXISTENTIAL_ID_tuple, 3, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_optional, EXISTENTIAL_ID_rotation };
    
    cr_assert_not(grphop_typeid_equal(lhs, rhs));
}

Test(typeid_equal, same)
{
    unsigned char lhs[] = { EXISTENTIAL_ID_tuple, 3, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_optional, EXISTENTIAL_ID_rotation };
    unsigned char rhs[] = { EXISTENTIAL_ID_tuple, 3, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_optional, EXISTENTIAL_ID_rotation };
    
    cr_assert(grphop_typeid_equal(lhs, rhs));
}

Test(typeid_equal, diff_cnt)
{
    unsigned char lhs[] = { EXISTENTIAL_ID_tuple, 3, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_integer, EXISTENTIAL_ID_optional, EXISTENTIAL_ID_rotation };
    unsigned char rhs[] = { EXISTENTIAL_ID_tuple, 3, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_pos, EXISTENTIAL_ID_optional, EXISTENTIAL_ID_rotation };
    
    cr_assert_not(grphop_typeid_equal(lhs, rhs));
}
