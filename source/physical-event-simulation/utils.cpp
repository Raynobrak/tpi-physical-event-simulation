#include "utils.h"

#include <cmath>
#include <sstream>
#include <iostream>

#include "constants.h"

std::string utils::float_to_fixed_string(float real, int digits) {
	std::stringstream stream;
	stream.precision(digits);
	stream << std::fixed;
	stream << real;

	auto str = stream.str();
	if (str == "-0.00")
		str = "0.00";

	return str;
}

const sf::Font& utils::get_default_font() {
    static const std::string FONT_PATH = "bebas_neue_font/BebasNeue-Regular.ttf";

    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        if (!font.loadFromFile(FONT_PATH)) {
            std::cout << "ERROR : Font '" + FONT_PATH + "' could not be loaded. A default font will be used." << std::endl;
        }
        fontLoaded = true;
    }

    return font;
}

const sf::Image& utils::get_application_icon_image() {
	const std::string ICON_PATH = "pes-icon.png";

	static bool loaded = false;
	static sf::Image icon;
	if (!loaded) {
		icon.loadFromFile(ICON_PATH);
		loaded = true;
	}
	return icon;
}