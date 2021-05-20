#include "ScaleIcon.h"
#include "constants.h"
#include "utils.h"

constexpr sf::Uint8 OPACITY_DELTA = 200u;
const sf::Color OPAQUE_COLOR = sf::Color(color_palette::LIGHT_TEXT);
const sf::Color SEMITRANSPARENT_COLOR = sf::Color(OPAQUE_COLOR.r, OPAQUE_COLOR.g, OPAQUE_COLOR.b, 255 - OPACITY_DELTA);

constexpr float SCALE_LENGTH_IN_METERS = 1.f;
constexpr float SCALE_WIDTH_HEIGHT_RATIO = 1.f / 10.f;
constexpr float LABEL_VERTICAL_OFFSET = -30.f;

ScaleIcon::ScaleIcon(ch::vec_t center, float pixelsPerMeter) : currentColor_(OPAQUE_COLOR) {
	const float SCALE_WIDTH = SCALE_LENGTH_IN_METERS * pixelsPerMeter;
	const float SCALE_HEIGHT = SCALE_WIDTH * SCALE_WIDTH_HEIGHT_RATIO;

	zone_ = ch::AABB(center - ch::vec_t(SCALE_WIDTH, SCALE_HEIGHT) / 2.f, { SCALE_WIDTH, SCALE_HEIGHT });

	label_.init(zone_, TINY_TEXT_SIZE, utils::float_to_fixed_string(SCALE_LENGTH_IN_METERS) + " mètres");
	label_.setPosition(zone_.pos + ch::vec_t(0.f, LABEL_VERTICAL_OFFSET));
}

void ScaleIcon::makeOpaque() {
	currentColor_ = OPAQUE_COLOR;
	label_.setTextColor(currentColor_);
}

void ScaleIcon::makeSemiTransparent() {
	currentColor_ = SEMITRANSPARENT_COLOR;
	label_.setTextColor(currentColor_);
}

void ScaleIcon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::VertexArray vertices(sf::PrimitiveType::Lines);

	vertices.append(sf::Vertex(zone_.pos, currentColor_));
	vertices.append(sf::Vertex(zone_.corner(ch::Corner::BottomLeft), currentColor_));

	vertices.append(sf::Vertex(zone_.corner(ch::Corner::TopRight), currentColor_));
	vertices.append(sf::Vertex(zone_.corner(ch::Corner::BottomRight), currentColor_));

	auto center = zone_.center();

	vertices.append(sf::Vertex({ zone_.pos.x, center.y }, currentColor_));
	vertices.append(sf::Vertex({ zone_.pos.x + zone_.size.x, center.y }, currentColor_));

	target.draw(vertices, states);

	target.draw(label_);
}
