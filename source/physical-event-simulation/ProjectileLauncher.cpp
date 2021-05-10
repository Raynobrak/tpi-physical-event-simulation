#include "ProjectileLauncher.h"

const sf::Color DEFAULT_LAUNCHER_BACKGROUND_COLOR = sf::Color(color_palette::LIGHT_FOREGROUND.r, color_palette::LIGHT_FOREGROUND.g, color_palette::LIGHT_FOREGROUND.b, 100);

ProjectileLauncher::ProjectileLauncher(ch::AABB zone) :
	projectile_(ch::Circle({ zone.pos.x + zone.size.x, zone.pos.y + zone.size.y / 2.f }, 20.f), ch::AABB(zone.pos, { zone.size.x * 10.f, zone.size.y }), true),
	slingshot_(zone, projectile_)
{
	zone_.setSize(zone.size);
	zone_.setPosition(zone.pos);
	zone_.setFillColor(DEFAULT_LAUNCHER_BACKGROUND_COLOR);

	projectile_.setFillColor(color_palette::DARK_GRAY	);

	topLeftInformations_.init(ch::AABB(zone.pos, { zone.size.x, zone.size.y / 4.f }), 20u, "informations\nsur\nplusieurs\nlignes");
	topLeftInformations_.setTextColor(color_palette::DARK_TEXT);

	projectileMass_ = 1.f;
}

void ProjectileLauncher::update(const sf::Event& event, ch::vec_t mousePosOnWindow) {
	if (projectile_.updateDragAndDrop(event, mousePosOnWindow))
		return;

	slingshot_.updateDragAndDrop(event, mousePosOnWindow);

	updateInformations();
}

void ProjectileLauncher::updateInformations() {
	float mass = 1.f;
	float velocity = slingshot_.getProjectileInitialVelocity();
	auto dir = slingshot_.getProjectileDirection();
	float angle = 180.f * atan2(-dir.y, dir.x) / ch::FLT_PI;

	std::string text = "Masse : " + std::to_string(mass) + " kg\n";
	text += "Vitesse initiale : " + std::to_string(velocity) + " m/s\n";
	text += "Angle : " + std::to_string(angle) + "°";

	topLeftInformations_.setText(text);
}

void ProjectileLauncher::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(zone_);
	target.draw(topLeftInformations_);
	target.draw(projectile_);
	target.draw(slingshot_);
}
