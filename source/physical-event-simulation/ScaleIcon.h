#pragma once

#include "color_palette.h"
#include <SFML/Graphics.hpp>
#include "Label.h"

class ScaleIcon : public sf::Drawable {
public:
	ScaleIcon(ch::vec_t center, float pixelsPerMeter);
	void makeOpaque();
	void makeSemiTransparent();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Color currentColor_;
	Label label_;
	ch::AABB zone_;
};

