#include "ProjectileLauncher.h"
#include "utils.h"

const sf::Color DEFAULT_LAUNCHER_BACKGROUND_COLOR = sf::Color(color_palette::LIGHT_FOREGROUND.r, color_palette::LIGHT_FOREGROUND.g, color_palette::LIGHT_FOREGROUND.b, 50);
constexpr float TEXT_MARGIN = 10.f;

ProjectileLauncher::ProjectileLauncher(ch::AABB zone, float pixelsPerMeter, float projectileRadiusInMeters) :
	projectile_(ch::Circle({ zone.pos.x + zone.size.x, zone.pos.y + zone.size.y / 2.f }, projectileRadiusInMeters * pixelsPerMeter), ch::AABB(zone.pos, { zone.size.x * 10.f, zone.size.y }), true),
	sling_(zone, projectile_, pixelsPerMeter),
	pixelsPerMeter_(pixelsPerMeter)
{
	zone_.setSize(zone.size);
	zone_.setPosition(zone.pos);
	zone_.setFillColor(DEFAULT_LAUNCHER_BACKGROUND_COLOR);

	auto color = color_palette::LIGHT_FOREGROUND;
	color.a = 120;
	projectile_.setFillColor(color);

	topLeftInformations_.init(ch::AABB(zone.pos + ch::vec_t{ TEXT_MARGIN, TEXT_MARGIN }, { 200.f, 80.f }), TINY_TEXT, "informations\nsur\nplusieurs\nlignes");
	topLeftInformations_.setTextColor(color_palette::DARK_TEXT);

	projectileMass_ = 1.f;
}

void ProjectileLauncher::update(const sf::Event& event, ch::vec_t mousePosOnWindow) {
	if (!projectile_.updateDragAndDrop(event, mousePosOnWindow)) {
		sling_.updateDragAndDrop(event, mousePosOnWindow);
	}

	if (event.type == sf::Event::MouseWheelMoved || event.type == sf::Event::KeyPressed) {
		int delta = 0;
		if (event.type == sf::Event::MouseWheelMoved) {
			delta = event.mouseWheel.delta;
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up) {
				delta = 1;
			}
			else if (event.key.code == sf::Keyboard::Down) {
				delta = -1;
			}
		}

		if (ch::collision::circle_contains(projectile_.getCircle(), mousePosOnWindow)) {
			projectileMass_ = std::min(std::max(projectileMass_ + delta * OBJ_MASS_INCREMENT, MIN_OBJ_MASS), MAX_OBJ_MASS);
		}
	}

	updateInformations();
}

CircleRigidBody ProjectileLauncher::constructCircleRigidBody() const {
	return CircleRigidBody(projectile_.getCircle(), projectileMass_, sling_.getProjectileInitialVelocityInMetersPerSecond() * sling_.getProjectileDirection() * pixelsPerMeter_ * SLINGSHOT_SPEED_MULTIPLIER);
}

void ProjectileLauncher::updateInformations() {
	float velocity = sling_.getProjectileInitialVelocityInMetersPerSecond();
	auto dir = sling_.getProjectileDirection();
	float angle = 180.f * atan2(-dir.y, dir.x) / ch::FLT_PI;

	std::string text = "Masse : " + utils::float_to_fixed_string(projectileMass_) + " kg\n";
	text += "Vitesse initiale : " + utils::float_to_fixed_string(velocity) + " m/s\n";
	text += "Angle : " + utils::float_to_fixed_string(angle) + "°";

	topLeftInformations_.setText(text);
}

void ProjectileLauncher::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(zone_);
	target.draw(topLeftInformations_);
	target.draw(projectile_);
	target.draw(sling_);
}
