#include "WindPicker.h"
#include "constants.h"

WindPicker::WindPicker(ch::vec_t center) : 
	clickableZone_(center, WINDPICKER_RADIUS),
	selectedPoint_(center - ch::vec_t(WINDPICKER_RADIUS, 0.f)),
	isDragging_(false)
{}

ch::vec_t WindPicker::computeWindIntensityAndDirection() const {
	auto delta = selectedPoint_ - clickableZone_.pos;
	float dist = ch::vec_magnitude(delta);
	float percentage = dist / WINDPICKER_RADIUS;
	float value = percentage * WINDPICKER_MAX_WIND_INTENSITY;
	auto dir = ch::vec_normalize(delta);
	return value * dir;
}

void WindPicker::update(sf::Event event, ch::vec_t mousePos) {
	bool leftHold = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	bool leftClick = event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left;
	bool leftRelease = event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left;
	
	bool mouseHoverSmallZone = ch::collision::circle_contains(clickableZone_, mousePos);

	if (mouseHoverSmallZone && leftClick) isDragging_ = true; 
	if (leftRelease) isDragging_ = false;

	if (isDragging_) {
		float dist = ch::vec_magnitude(mousePos - clickableZone_.pos);
		dist = std::min(dist, clickableZone_.radius);
		selectedPoint_ = clickableZone_.pos + ch::vec_normalize(mousePos - clickableZone_.pos) * dist;
	}
}

VectorArrow WindPicker::buildWindArrow() const {
	return VectorArrow(selectedPoint_ - clickableZone_.pos, clickableZone_.pos);
}

void WindPicker::draw(sf::RenderTarget& target, sf::RenderStates) const {
	sf::CircleShape zone;
	zone.setRadius(clickableZone_.radius);
	auto color = color_palette::LIGHT_FOREGROUND;
	color.a = 80;
	zone.setFillColor(sf::Color::Transparent);
	zone.setOutlineColor(color);
	zone.setOutlineThickness(2.f);
	zone.setPosition(ch::collision::enclosingAABB(clickableZone_).pos);
	target.draw(zone);

	target.draw(buildWindArrow());
}
