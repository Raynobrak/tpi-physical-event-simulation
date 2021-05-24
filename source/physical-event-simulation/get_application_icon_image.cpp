#include "get_application_icon_image.h"

const std::string ICON_PATH = "pes-icon.png";

const sf::Image& get_application_icon_image() {
	static bool loaded = false;
	static sf::Image icon;
	if (!loaded) {
		icon.loadFromFile(ICON_PATH);
		loaded = true;
	}
	return icon;
}