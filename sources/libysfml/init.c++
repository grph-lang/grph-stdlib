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
#include "ns/standard.h"
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

extern "C" void grphg_update(void)
{
    sf::RenderWindow &window = getWindow();
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(0);
        }
    }
    grph_color_t *color = (grph_color_t *) grphv_global_back->paint.data;
    window.clear(sf::Color(color->red, color->green, color->blue));
    window.display();
}

extern "C" void grphg_init(void)
{
    struct grph_existential paint = { return_color_typetable(), {0} };
    grphv_global_back = grphc_Background({640, 480}, &paint);
    grphg_update();
}

extern "C" void grphg_update_back(void)
{
    sf::RenderWindow &window = getWindow();

    window.setSize(sf::Vector2u(grphv_global_back->size.x, grphv_global_back->size.y));
    window.setView(sf::View(sf::FloatRect(0, 0, grphv_global_back->size.x, grphv_global_back->size.y)));
    sf::sleep(sf::Time(sf::milliseconds(8)));
    grphg_update();
}
