#include "Label.h"
#include "utils.h"

const sf::Color DEFAULT_TEXT_FORECOLOR = color_palette::LIGHT_TEXT;

Label::Label() {
}

Label::Label(ch::AABB zone, unsigned characterSize, std::string text) {
	init(zone, characterSize, text);
}

void Label::init(ch::AABB zone, unsigned characterSize, std::string text) {
	textZone_ = zone;
	text_.setCharacterSize(characterSize);
	text_.setString(text);
	text_.setFont(utils::get_default_font());
	text_.setFillColor(DEFAULT_TEXT_FORECOLOR);
	centerText();
}

void Label::setText(std::string str) {
	text_.setString(str);
	centerText();
}

void Label::setPosition(ch::vec_t newPos) {
	textZone_.pos = newPos;
	centerText();
}

void Label::setTextColor(sf::Color newColor) {
	text_.setFillColor(newColor);
}

ch::AABB Label::getZone() const {
	return textZone_;
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	/*sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(sf::Color::Red);
	shape.setSize(textZone_.size);
	shape.setPosition(textZone_.pos);
	target.draw(shape);*/

	target.draw(text_);
}

void Label::centerText() {
	auto bounds = text_.getLocalBounds();
	text_.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	text_.setPosition(textZone_.center());
}
