#include "ConfigurableCircle.h"
#include "utils.h"

ConfigurableCircle::ConfigurableCircle(ch::Circle circle, ch::AABB zone, float defaultMass) : 
	draggableCircle_(circle, zone, false), 
	mass_(defaultMass),
	massLabel_(ch::collision::enclosingAABB(circle), 20u, "---")
{
	massLabel_.setTextColor(color_palette::DARK_TEXT);
}

bool ConfigurableCircle::update(const sf::Event& event, ch::vec_t mousePosOnWindow) {
	bool updated = draggableCircle_.updateDragAndDrop(event, mousePosOnWindow);

	if (event.type == sf::Event::MouseWheelMoved) {
		if (ch::collision::circle_contains(draggableCircle_.getCircle(), mousePosOnWindow)) {
			auto delta = event.mouseWheel.delta;
			mass_ = std::min(std::max(mass_ + delta * OBJ_MASS_INCREMENT, MIN_OBJ_MASS), MAX_OBJ_MASS);
		}
	}

	massLabel_.setPosition(ch::collision::enclosingAABB(draggableCircle_.getCircle()).pos);
	massLabel_.setText(utils::float_to_fixed_string(mass_));

	return updated;
}

ch::Circle ConfigurableCircle::getCircle() const{
	return draggableCircle_.getCircle();
}

CircleRigidBody ConfigurableCircle::constructCircleRigidBody() const {
	return CircleRigidBody(draggableCircle_.getCircle(), mass_);
}

void ConfigurableCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	auto circle = draggableCircle_.getCircle();
	sf::CircleShape shape_;
	shape_.setRadius(circle.radius);
	shape_.setPosition(ch::collision::enclosingAABB(circle).pos);
	shape_.setFillColor(color_palette::LIGHT_FOREGROUND);
	target.draw(shape_);
	target.draw(massLabel_);
}
