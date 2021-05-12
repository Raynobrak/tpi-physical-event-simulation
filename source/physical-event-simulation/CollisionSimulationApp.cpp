#include "CollisionSimulationApp.h"
#include <iostream>

constexpr float SIMULATION_WINDOW_HEIGHT = 500.f;
constexpr float SIMULATION_WINDOW_WIDTH = 800.f;
constexpr float LAUNCHER_WIDTH = 300.f;
constexpr float OBJECTS_BOUNDARIES_WIDTH = SIMULATION_WINDOW_WIDTH - LAUNCHER_WIDTH;

constexpr float BUTTON_MARGIN = 20.f;
constexpr float BUTTON_WIDTH = 80.f;
constexpr float BUTTON_HEIGHT = 40.f;

CollisionSimulationApp::CollisionSimulationApp() : 
	launcher_(ch::AABB({ 0.f,0.f }, { LAUNCHER_WIDTH, SIMULATION_WINDOW_HEIGHT })),
	launchSimulationButton_(ch::AABB(LAUNCHER_WIDTH + BUTTON_MARGIN, BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT), 20u, "---"),
	simulationRunning_(false)
{
	SFMLApplicationSettings settings;
	settings.applicationName = "Expérience de collisions élastiques";
	settings.windowWidth = SIMULATION_WINDOW_WIDTH;
	settings.windowHeight = SIMULATION_WINDOW_HEIGHT;
	settings.backgroundColor = color_palette::VERY_DARK_GRAY;
	initApplication(settings);

	launchSimulationButton_.setTextColor(color_palette::DARK_TEXT);
	updateLaunchButtonText();

	spawnRandomCircles();

	//configurableCircles_.push_back(ConfigurableCircle(ch::Circle({ 400.f, 200.f }, P_OBJECTS_RADIUS), editableZone));
}

void CollisionSimulationApp::handleEvent(sf::Event& event) {
	switch (event.type) {
	case sf::Event::KeyPressed:
		switch (event.key.code) {

		}
		break;
	case sf::Event::Closed:
		exitApplication();
		break;
	}

	auto mouse = getMousePosOnWindow();

	

	if (launchSimulationButton_.checkForMouseRelease(mouse, event)) {
		switchSimulationMode();
	}

	if (simulationRunning_) {
		
	}
	else {
		launcher_.update(event, mouse);

		for (auto& configurableCircle : configurableCircles_) {
			if (configurableCircle.update(event, mouse)) {
				break;
			}
		}
	}
}

void CollisionSimulationApp::update(float dt) {
	if (simulationRunning_) {
		//float energy = 0.f;
		for (auto& object : circleRigidBodies_) {
			object.collideWithWalls(ch::AABB(0.f, 0.f, SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT));
			object.update(dt);
			//energy += object.computeKineticEnergy();
		}
		//std::cout << energy << std::endl;

		for (size_t i = 0; i < circleRigidBodies_.size(); ++i) {
			for (size_t j = i; j < circleRigidBodies_.size(); ++j) {
				circleRigidBodies_[i].collideWith(circleRigidBodies_[j]);
			}
		}
	}
}

void CollisionSimulationApp::customRender() {
	drawOnWindow(launchSimulationButton_);

	if (simulationRunning_) {
		for (const auto& body : circleRigidBodies_)
			drawOnWindow(body);
	}
	else {
		for (const auto& c : configurableCircles_)
			drawOnWindow(c);
		drawOnWindow(launcher_);
	}

}

void CollisionSimulationApp::updateLaunchButtonText() {
	launchSimulationButton_.setText(simulationRunning_ ? "Stop" : "Lancer");
}

void CollisionSimulationApp::switchSimulationMode() {
	simulationRunning_ = !simulationRunning_;
	updateLaunchButtonText();

	if (simulationRunning_) {
		circleRigidBodies_.push_back(launcher_.constructCircleRigidBody());
		for (const auto& c : configurableCircles_) {
			circleRigidBodies_.push_back(c.constructCircleRigidBody());
		}
	}
	else {
		circleRigidBodies_.clear();
	}
}

void CollisionSimulationApp::spawnRandomCircles() {
	ch::AABB editableZone({ LAUNCHER_WIDTH + P_OBJECTS_RADIUS, 0.f }, { SIMULATION_WINDOW_WIDTH - LAUNCHER_WIDTH - P_OBJECTS_RADIUS, SIMULATION_WINDOW_HEIGHT });

	configurableCircles_.clear();

	while (configurableCircles_.size() < OBJECTS_COUNT) {
		auto randomPosition = ch::rand::rand_point_on_rect(editableZone.pos, editableZone.size);
		ch::Circle newObject(randomPosition, P_OBJECTS_RADIUS);

		if (ch::collision::aabb_contains(editableZone, newObject)) {
			bool collidesWithAny = false;
			for (const auto& otherCircle : configurableCircles_) {
				if (ch::collision::circle_intersects(newObject, otherCircle.getCircle())) {
					collidesWithAny = true;
					break;
				}
			}

			if (!collidesWithAny) {
				configurableCircles_.push_back(ConfigurableCircle(newObject, editableZone));
			}
		}
	}
}
