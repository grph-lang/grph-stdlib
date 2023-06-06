//
//  init.c++
//  GRPH stdlib - libysfml
//
//  Created by Emil Pedersen on 06/06/2023.
// 
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//

extern "C" {
#include "grph_shapes.h"
#include "grph_types.h"
}

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

extern "C" {
    grph_Background_t *grphv_global_back = nullptr;
    struct typetable *return_color_typetable(void);
}

sf::RenderWindow &getWindow()
{
    static sf::RenderWindow window(sf::VideoMode(640, 480), "GRPH");
    return window;
}

extern "C" void grphg_init(void)
{
    grphv_global_back = grphc_Background({640, 480}, { return_color_typetable(), {0} });
    sf::RenderWindow &window = getWindow();
    window.clear(sf::Color::Black);
    window.display();
}
