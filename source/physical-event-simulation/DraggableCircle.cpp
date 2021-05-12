#include "DraggableCircle.h"

DraggableCircle::DraggableCircle(ch::Circle circle, ch::AABB boundaries, bool lockedHorizontally) : circle_(circle), boundaries_(boundaries), lockedHorizontally_(lockedHorizontally), isDragging_(false) {
	circleShape_.setRadius(circle_.radius);
	circleShape_.setFillColor(sf::Color::Cyan);
	circleShape_.setOrigin(circle.radius, circle.radius);

	updatePosition(circle_.pos);
}

ch::vec_t DraggableCircle::getCirclePos() const {
	return circle_.pos;
}

ch::Circle DraggableCircle::getCircle() const {
	return circle_;
}

bool DraggableCircle::updateDragAndDrop(const sf::Event& event, ch::vec_t mousePosOnWindow) {
	bool leftClick = event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;
	bool leftRelease = event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left;

	if (leftClick) {
		if (isHovered(mousePosOnWindow)) {
			isDragging_ = true;
			dragOrigin_ = mousePosOnWindow - circle_.pos;
		}
	}
	else if(leftRelease) {
		isDragging_ = false;
	}
	else {
		if (isDragging_) {
			updatePosition(mousePosOnWindow - dragOrigin_);
		}
	}

	return isDragging_;
}

void DraggableCircle::setFillColor(sf::Color newColor) {
	circleShape_.setFillColor(newColor);
}

void DraggableCircle::setOutlineColor(sf::Color newColor) {
	circleShape_.setOutlineThickness(1.f);
	circleShape_.setOutlineColor(newColor);
}

bool DraggableCircle::isHovered(ch::vec_t mousePos) const {
	return ch::collision::circle_contains(circle_, mousePos);
}

void DraggableCircle::updatePosition(ch::vec_t newPos) {
	if (ch::collision::aabb_contains(boundaries_, ch::Circle(newPos, circle_.radius))) {
		if (lockedHorizontally_)
			newPos.x = circle_.pos.x;

		circle_.pos = newPos;
		circleShape_.setPosition(circle_.pos);
	}
	//else {
	//	isDragging_ = false;
	//}
}

void DraggableCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	/*sf::RectangleShape zone;
	zone.setPosition(boundaries_.pos);
	zone.setSize(boundaries_.size);
	zone.setFillColor(sf::Color::Transparent);
	zone.setOutlineColor(sf::Color::White);
	zone.setOutlineThickness(1.f);
	target.draw(zone);*/

	target.draw(circleShape_);
}
