#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>

const sf::Color DEFAULT_ARROW_COLOR = sf::Color::White;

class VectorArrow : public sf::Drawable {
public:
	VectorArrow(ch::vec_t value = ch::NULL_VEC, ch::vec_t origin = ch::NULL_VEC, sf::Color color = DEFAULT_ARROW_COLOR);
	void setLength(ch::vec_t newLength);
	void setOrigin(ch::vec_t newOrigin);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	ch::vec_t origin_;
	ch::vec_t length_;

	sf::Color color_;
};

