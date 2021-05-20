#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>

class DraggableCircle : public sf::Drawable {
public:
	DraggableCircle(ch::Circle circle, ch::AABB boundaries, bool lockHorizontally = false);
	ch::vec_t getCirclePos() const;
	ch::Circle getCircle() const;
	bool updateDragAndDrop(const sf::Event& event, ch::vec_t mousePosOnWindow);
	void setFillColor(sf::Color newColor);
	void setOutlineColor(sf::Color newColor);
protected:
	ch::Circle circle_;
	ch::AABB boundaries_;
private:
	bool isHovered(ch::vec_t mousePos) const;
	void updatePosition(ch::vec_t newPos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::CircleShape circleShape_;

	bool lockedHorizontally_;
	bool isDragging_;
	ch::vec_t dragOrigin_;

};

