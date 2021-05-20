#pragma once

#include "DraggableCircle.h"
#include "CircleRigidBody.h"

class TargetSlider : public DraggableCircle {
public:
	TargetSlider(float xPos, float height, float targetRadius);
	void update(sf::Event event, ch::vec_t mousePos);
	bool checkForCollision(const CircleRigidBody& body) const;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::VertexArray sliderRail_;
};

