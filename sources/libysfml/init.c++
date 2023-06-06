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

#include "grph_types.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

sf::RenderWindow &getWindow()
{
    static sf::RenderWindow window(sf::VideoMode(800, 600), "GRPH");
    return window;
}

extern "C" void grphg_init(void)
{
    sf::RenderWindow &window = getWindow();
    window.setFramerateLimit(60);
}
