//
//  vwt.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 26/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef vwt_h
#define vwt_h

#include "typetable.h"

copy_func grphvwt_copy_trivial;
destroy_func grphvwt_destroy_trivial;

copy_func grphvwt_retain_ref;
destroy_func grphvwt_release_ref;

copy_func grphvwt_copy_mixed;
destroy_func grphvwt_destroy_mixed;

copy_func grphvwt_copy_optional;
destroy_func grphvwt_destroy_optional;

copy_func grphvwt_copy_tuple;
destroy_func grphvwt_destroy_tuple;

copy_func grphvwt_retain_string;
destroy_func grphvwt_release_string;

copy_func grphvwt_retain_font;
destroy_func grphvwt_release_font;

#endif /* vwt_h */
