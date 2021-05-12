#include "CircleRigidBody.h"
#include "utils.h"

CircleRigidBody::CircleRigidBody(ch::Circle circle, float mass, ch::vec_t initialVelocity) : circle_(circle), mass_(mass), vel_(initialVelocity), timeSinceLastTraceSave_(0.f) {}

void CircleRigidBody::collideWithWalls(ch::AABB enclosingWalls) {
	if (!ch::collision::aabb_contains(enclosingWalls, circle_)) {
		auto circleAABB = ch::collision::enclosingAABB(circle_);
		auto collision = ch::collision::aabb_collision_info(enclosingWalls, circleAABB);
		move((circle_.diameter() - collision.absolutePenetrationDepthAlongNormal()) * -collision.normal);
		accelerate(ch::vec_dot_product(vel_, -collision.normal) * collision.normal * 2.f);
	}
}

void CircleRigidBody::accelerate(ch::vec_t acceleration) {
	vel_ += acceleration;
}

void CircleRigidBody::move(ch::vec_t translationVector) {
	circle_.pos += translationVector;
}

void CircleRigidBody::update(float dt) {
	move(dt * vel_);

	timeSinceLastTraceSave_ += dt;
	if (timeSinceLastTraceSave_ > OBJECTS_TIME_BETWEEN_TRACE_SAVE) {
		timeSinceLastTraceSave_ = 0.f;
		savePosition();
	}
}

void CircleRigidBody::collideWith(CircleRigidBody& other) {
	auto coll = ch::collision::circles_collision_info(circle_, other.circle_);
	auto movement = coll.normal * coll.absoluteDepth / 2.f;

	move(-movement);
	other.move(movement);

	float impulse = (ch::vec_dot_product(2.f * coll.normal, other.vel_ - vel_) / (inverseMass() + other.inverseMass()));
	accelerate(impulse * coll.normal / mass_);
	other.accelerate(-impulse * coll.normal / other.mass_);
}

float CircleRigidBody::computeKineticEnergy() const {
	auto vel = ch::vec_magnitude(vel_);
	return mass_ / 2.f * vel * vel;
}

float CircleRigidBody::inverseMass() const {
	return 1.f / mass_;
}

void CircleRigidBody::savePosition() {
	trace_.push_back(circle_.pos);
	if (trace_.size() > OBJECTS_TRACE_HISTORY_LENGTH) {
		trace_.pop_front();
	}
}

void CircleRigidBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	/*sf::Color outline = color_palette::LIGHT_FOREGROUND;
	outline.a = 0;
	float radius = 0;
	for (const auto& pos : trace_) {
		sf::CircleShape shape(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(pos);
		shape.setFillColor(outline);
		shape.setOutlineThickness(1.f);
		shape.setOutlineColor(outline);
		target.draw(shape);
		outline.a += (255 / OBJECTS_TRACE_HISTORY_LENGTH);
		radius += (circle_.radius / OBJECTS_TRACE_HISTORY_LENGTH);
	}*/

	sf::CircleShape shape(circle_.radius);
	shape.setOrigin(circle_.radius, circle_.radius);
	shape.setPosition(circle_.pos);
	shape.setFillColor(color_palette::LIGHT_FOREGROUND);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(sf::Color::Black);
	target.draw(shape);
}
