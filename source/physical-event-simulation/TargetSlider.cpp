#include "TargetSlider.h"

constexpr float SLIDER_RAIL_THICKNESS = 5.f;
constexpr float ZONE_WIDTH = 300.f;

TargetSlider::TargetSlider(float xPos, float height, float targetRadius) :
	DraggableCircle(ch::Circle({ xPos, height / 2.f }, targetRadius), ch::AABB(xPos - ZONE_WIDTH / 2.f, 0.f, ZONE_WIDTH, height), true)
{
	sliderRail_.setPrimitiveType(sf::PrimitiveType::Quads);

	ch::AABB railZone(circle_.pos.x - SLIDER_RAIL_THICKNESS / 2.f, 0.f, SLIDER_RAIL_THICKNESS, boundaries_.size.y);
	auto railColor = color_palette::DARK_GRAY;

	sliderRail_.append(sf::Vertex(railZone.corner(ch::Corner::TopLeft), railColor));
	sliderRail_.append(sf::Vertex(railZone.corner(ch::Corner::TopRight), railColor));
	sliderRail_.append(sf::Vertex(railZone.corner(ch::Corner::BottomRight), railColor));
	sliderRail_.append(sf::Vertex(railZone.corner(ch::Corner::BottomLeft), railColor));
}

void TargetSlider::update(sf::Event event, ch::vec_t mousePos) {
	updateDragAndDrop(event, mousePos);
}

bool TargetSlider::checkForCollision(const CircleRigidBody& body) const {
	return ch::collision::circle_intersects(body.getCircle(), circle_);
}

void TargetSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sliderRail_);

	sf::CircleShape shape_;
	shape_.setRadius(circle_.radius);
	shape_.setPosition(ch::collision::enclosingAABB(circle_).pos);
	shape_.setFillColor(color_palette::LIGHT_FOREGROUND);
	target.draw(shape_, states);
}
