#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>
#include "DraggableCircle.h"
#include "color_palette.h"
#include "constants.h"

class LauncherSling : public sf::Drawable {
public:
	LauncherSling(ch::AABB zone, const DraggableCircle& circle, float pixelsPerMeter);
	void updateDragAndDrop(const sf::Event& event, ch::vec_t mousePosOnWindow);
	ch::vec_t getProjectileDirection() const;
	float getProjectileInitialVelocityInMetersPerSecond() const;
	bool isProjectileHovered(ch::vec_t mousePos) const;
private:
	void updatePosition(ch::vec_t newPos);
private:
	sf::RectangleShape rectShape_;
	ch::AABB zone_;
	ch::AABB rect_;
	const DraggableCircle& circle_;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float pixelsPerMeter_;
};

