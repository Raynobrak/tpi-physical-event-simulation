#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>

#include <iostream>

#include "color_palette.h"

class Label : public sf::Drawable {
public:
	Label();
	Label(ch::AABB zone, unsigned characterSize, std::string text);
	void init(ch::AABB zone, unsigned characterSize, std::string text);
	void setText(std::string str);
	void setPosition(ch::vec_t newPos);
	void setTextColor(sf::Color newColor);

	ch::AABB getZone() const;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void centerText();

	ch::AABB textZone_;
	sf::Text text_;
};

