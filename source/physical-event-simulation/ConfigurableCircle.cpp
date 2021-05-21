#include "ConfigurableCircle.h"
#include "utils.h"

ConfigurableCircle::ConfigurableCircle(ch::Circle circle, ch::AABB boundaries, float defaultMass) : 
	DraggableCircle(circle, boundaries, false),
	mass_(defaultMass),
	massLabel_(ch::collision::enclosingAABB(circle), TINY_TEXT, "---")
{
	massLabel_.setTextColor(color_palette::DARK_TEXT);
}

bool ConfigurableCircle::update(const sf::Event& event, ch::vec_t mousePosOnWindow) {
	bool updated = updateDragAndDrop(event, mousePosOnWindow);

	if (event.type == sf::Event::MouseWheelMoved) {
		if (ch::collision::circle_contains(circle_, mousePosOnWindow)) {
			auto delta = event.mouseWheel.delta;
			mass_ = std::min(std::max(mass_ + delta * OBJ_MASS_INCREMENT, MIN_OBJ_MASS), MAX_OBJ_MASS);
		}
	}

	massLabel_.setPosition(ch::collision::enclosingAABB(circle_).pos);
	massLabel_.setText(utils::float_to_fixed_string(mass_));

	return updated;
}

ch::Circle ConfigurableCircle::getCircle() const{
	return circle_;
}

CircleRigidBody ConfigurableCircle::constructCircleRigidBody() const {
	return CircleRigidBody(circle_, mass_);
}

void ConfigurableCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::CircleShape shape_;
	shape_.setRadius(circle_.radius);
	shape_.setPosition(ch::collision::enclosingAABB(circle_).pos);
	shape_.setFillColor(color_palette::LIGHT_FOREGROUND);
	target.draw(shape_);
	target.draw(massLabel_);
}
