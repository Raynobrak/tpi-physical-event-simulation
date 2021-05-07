#pragma once

#include "get_default_font.h"
#include <iostream>

const sf::Font& get_default_font() {
    static const std::string FONT_PATH = "bebas_neue_font/BebasNeue-Regular.ttf";

    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        if (!font.loadFromFile(FONT_PATH)) {
            std::cout << "ERROR : Font '"+ FONT_PATH +"' could not be loaded." << std::endl;
        }
        fontLoaded = true;
    }
    
    return font;
}
