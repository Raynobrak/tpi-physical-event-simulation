#pragma once

#include <SFML/Graphics.hpp>

// Structure permettant de stocker les paramètre d'une application SFML.
// S'utilise cojointement avec la classe SFMLApplicationBase.
struct SFMLApplicationSettings {
	std::string applicationName = "SFML Application";
	unsigned windowWidth = DEFAULT_WINDOW_WIDTH;
	unsigned windowHeight = DEFAULT_WINDOW_HEIGHT;
	float fps = DEFAULT_FPS;
	float fixedTimeStep = DEFAULT_FIXED_TIME_STEP;
	sf::Color backgroundColor = sf::Color::Black;

private:
	static constexpr unsigned DEFAULT_WINDOW_WIDTH = 400;
	static constexpr unsigned DEFAULT_WINDOW_HEIGHT = 300;
	static constexpr float DEFAULT_FPS = 60.f;
	static constexpr float DEFAULT_FIXED_TIME_STEP = 0.01f;
};