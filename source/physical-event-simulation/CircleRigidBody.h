#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>
#include "constants.h"
#include "color_palette.h"
#include <deque>

class CircleRigidBody : public sf::Drawable {
public:
	CircleRigidBody(ch::Circle circle = ch::Circle(), float mass = 0.f, ch::vec_t initialVelocity = ch::NULL_VEC);
	void collideWithWalls(ch::AABB enclosingWalls);
	void accelerate(ch::vec_t acceleration);
	void move(ch::vec_t translationVector);	
	void update(float dt);
	void collideWith(CircleRigidBody& other);
	float computeKineticEnergy() const;
private:
	float inverseMass() const;
	void savePosition();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	ch::Circle circle_;
	ch::vec_t vel_;
	float mass_;

	std::deque<ch::vec_t> trace_;
	float timeSinceLastTraceSave_;
};

