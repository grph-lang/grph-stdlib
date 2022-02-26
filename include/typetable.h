//
//  typetable.h
//  GRPH stdlib - libgrph
//
//  Created by Emil Pedersen on 26/02/2022.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

#ifndef typetable_h
#define typetable_h

struct typetable {
    /// A pointer to the nil terminated name of the specialized type
    /// the precedent char, `tt.type_name[-1]`, is the typeid char
    char *type_name;
    // Add more fields here, including the vwt
    /// The generics vector, inline, null terminated
    struct typetable *generics[0];
};

#define TYPETABLE_TYPEID_CHAR(tt) ((existential_type_id_t) (tt).type_name[-1])

#endif /* typetable_h */
