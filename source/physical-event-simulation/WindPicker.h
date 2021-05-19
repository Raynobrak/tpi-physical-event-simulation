#pragma once

#include "Label.h"

class WindPicker : public sf::Drawable {
public:
	WindPicker(ch::vec_t center);
	ch::vec_t computeWindIntensityAndDirection() const;
	void update(sf::Event event, ch::vec_t mousePos);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
private:
	ch::Circle zone_;
};

