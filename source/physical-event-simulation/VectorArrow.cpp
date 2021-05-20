#include "VectorArrow.h"

VectorArrow::VectorArrow(ch::vec_t value, ch::vec_t origin, sf::Color color) : origin_(origin), length_(value), color_(color) {}

void VectorArrow::setLength(ch::vec_t newLength) {
	length_ = newLength;
}

void VectorArrow::setOrigin(ch::vec_t newOrigin) {
	origin_ = newOrigin;
}

void VectorArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray vertices(sf::PrimitiveType::Lines);

	constexpr float ARROW_FEATHER_PROPORTION_TO_LENGTH = 0.2f;
	constexpr float ARROW_FEATHERS_ANGLE = 40.f;

	auto start = origin_;
	auto end = origin_ + length_;
	auto towardsStart = start - end;

	vertices.append(sf::Vertex(start, color_));
	vertices.append(sf::Vertex(end, color_));

	vertices.append(sf::Vertex(end, color_));
	vertices.append(sf::Vertex(end + ch::vec_rotate(towardsStart, ARROW_FEATHERS_ANGLE) * ARROW_FEATHER_PROPORTION_TO_LENGTH, color_));

	vertices.append(sf::Vertex(end, color_));
	vertices.append(sf::Vertex(end + ch::vec_rotate(towardsStart, -ARROW_FEATHERS_ANGLE) * ARROW_FEATHER_PROPORTION_TO_LENGTH, color_));

	target.draw(vertices, states);
}
