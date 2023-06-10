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

sf::RenderWindow &getWindow();


extern "C" void grphg_draw_Rectangle(grph_Rectangle_t *subject)
{
    grph_color_t *color = (grph_color_t *) subject->paint.data;
    sf::Color sfcolor(color->red, color->green, color->blue, color->alpha * 255);
    sf::RectangleShape rect({ static_cast<float>(subject->size.x), static_cast<float>(subject->size.y) });
    sf::RenderWindow &window = getWindow();

    rect.setPosition(subject->pos.x, subject->pos.y);
    rect.setRotation(subject->rotation);
    if (subject->filling) {
        rect.setOutlineColor(sf::Color::Transparent);
        rect.setFillColor(sfcolor);
    } else {
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sfcolor);
        rect.setOutlineThickness(subject->strokeWidth);
    }
    window.draw(rect);
}
