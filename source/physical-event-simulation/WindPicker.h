#pragma once

#include "Label.h"
#include "VectorArrow.h"

class WindPicker : public sf::Drawable {
public:
	WindPicker(ch::vec_t center);
	ch::vec_t computeWindIntensityAndDirection() const;
	void update(sf::Event event, ch::vec_t mousePos);
	VectorArrow buildWindArrow() const;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
private:
	ch::Circle clickableZone_;
	ch::vec_t selectedPoint_;
	bool isDragging_;
};

