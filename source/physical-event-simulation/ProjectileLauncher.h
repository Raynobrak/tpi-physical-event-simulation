#pragma once

#include <SFML/Graphics.hpp>
#include "Label.h"
#include "DraggableCircle.h"
#include "LauncherSling.h"

class ProjectileLauncher : public sf::Drawable {
public:
	ProjectileLauncher(ch::AABB zone);
	void update(const sf::Event& event, ch::vec_t mousePosOnWindow);
private:
	void updateInformations();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	Label topLeftInformations_;
	sf::RectangleShape zone_;
	//sf::CircleShape projectile_;
	//ch::Circle projectileHitbox_;
	DraggableCircle projectile_;
	LauncherSling slingshot_;
	float projectileMass_;
};

