#pragma once

#include <SFML/Graphics.hpp>
#include "CircleRigidBody.h"
#include "DraggableCircle.h"
#include "Label.h"

class ConfigurableCircle : public DraggableCircle {
public:
	ConfigurableCircle(ch::Circle circle, ch::AABB zone, float defaultMass = 1.f);
	bool update(const sf::Event& event, ch::vec_t mousePosOnWindow);
	ch::Circle getCircle() const;
	CircleRigidBody constructCircleRigidBody() const;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	float mass_;
	Label massLabel_;
};

