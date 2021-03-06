#include "LauncherSling.h"

constexpr float SLINGSHOT_HANDLE_WIDTH = 20.f;

LauncherSling::LauncherSling(ch::AABB zone, const DraggableCircle& circle, float pixelsPerMeter) : projectile_(circle), boundaries_(zone), pixelsPerMeter_(pixelsPerMeter) {
	rect_.size = { SLINGSHOT_HANDLE_WIDTH, SLINGSHOT_HANDLE_WIDTH };
	rect_.pos = zone.center() - rect_.size / 2.f;

	rectShape_.setPosition(rect_.pos);
	rectShape_.setSize(rect_.size);
	rectShape_.setFillColor(color_palette::DARK_GRAY);
}

void LauncherSling::updateDragAndDrop(const sf::Event& event, ch::vec_t mousePosOnWindow) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		updatePosition(mousePosOnWindow - rect_.size / 2.f);
	}
}

ch::vec_t LauncherSling::getProjectileDirection() const {
	return ch::vec_normalize(projectile_.getCirclePos() - rect_.center());
}

float LauncherSling::getProjectileInitialVelocityInMetersPerSecond() const {
	return ch::vec_magnitude(projectile_.getCirclePos() - rect_.center()) / pixelsPerMeter_;
}

bool LauncherSling::isProjectileHovered(ch::vec_t mousePos) const {
	return ch::collision::circle_contains(projectile_.getCircle(), mousePos);
}

void LauncherSling::updatePosition(ch::vec_t newPos) {
	if (ch::collision::aabb_contains(boundaries_, ch::AABB(newPos, rect_.size))) {
		rect_.pos = newPos;
		rectShape_.setPosition(rect_.pos);
	}
}

void LauncherSling::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rectShape_);
	sf::VertexArray line(sf::PrimitiveType::Lines);
	line.append(sf::Vertex(rect_.center(), color_palette::LIGHT_TEXT));
	line.append(sf::Vertex(projectile_.getCirclePos(), color_palette::LIGHT_TEXT));
	target.draw(line);
}
