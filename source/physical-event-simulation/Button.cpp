#include "Button.h"

Button::Button() {}

Button::Button(ch::AABB clickableZone, unsigned characterSize, std::string text) {
	init(clickableZone, characterSize, text);
}

void Button::init(ch::AABB clickableZone, unsigned characterSize, std::string text) {
	buttonLabel_.init(clickableZone, characterSize, text);
	isClicked_ = false;
}

bool Button::checkForMouseRelease(ch::vec_t mousePos, sf::Event event) {
	bool leftClick = event.mouseButton.button == sf::Mouse::Left;

	if (event.type == sf::Event::MouseButtonPressed && leftClick) {
		if (isHovered(mousePos)) {
			isClicked_ = true;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && leftClick) {
		if (isHovered(mousePos)) {
			if (isClicked_) {
				isClicked_ = false;
				return true;
			}
		}
		isClicked_ = false;
	}
	
	return false;
}

bool Button::isHovered(ch::vec_t mousePos) const {
	return ch::collision::aabb_contains(buttonLabel_.getZone(), mousePos);
}

void Button::setTextColor(sf::Color newColor) {
	buttonLabel_.setTextColor(newColor);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	auto zone = buttonLabel_.getZone();

	sf::RectangleShape shape;
	shape.setPosition(zone.pos);
	shape.setSize(zone.size);
	shape.setFillColor(isClicked_ ? color_palette::DARK_GRAY : color_palette::LIGHT_FOREGROUND);
	//shape.setOutlineThickness(1.f);
	//shape.setOutlineColor(sf::Color::Red);
	target.draw(shape);

	target.draw(buttonLabel_);
}
