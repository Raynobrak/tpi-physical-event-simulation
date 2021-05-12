#pragma once

#include "Label.h"

class Button : public sf::Drawable {
public:
	Button();
	Button(ch::AABB clickableZone, unsigned characterSize, std::string text);
	void init(ch::AABB clickableZone, unsigned characterSize, std::string text);
	bool checkForMouseRelease(ch::vec_t mousePos, sf::Event event);
	bool isHovered(ch::vec_t mousePos) const;
	void setText(std::string newText);
	void setTextColor(sf::Color newColor);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	Label buttonLabel_;

	bool isClicked_;
};

