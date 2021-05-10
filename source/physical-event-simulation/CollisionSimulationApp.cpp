#include "CollisionSimulationApp.h"

constexpr float SIMULATION_WINDOW_HEIGHT = 500.f;
constexpr float SIMULATION_WINDOW_WIDTH = 800.f;
constexpr float LAUNCHER_WIDTH = 300.f;
constexpr float OBJECTS_BOUNDARIES_WIDTH = SIMULATION_WINDOW_WIDTH - LAUNCHER_WIDTH;

CollisionSimulationApp::CollisionSimulationApp() : 
	launcher_(ch::AABB({ 0.f,0.f }, { 300.f, SIMULATION_WINDOW_HEIGHT })),
	object_(ch::Circle({ 350.f,300.f }, 10.f), ch::AABB(LAUNCHER_WIDTH, 0.f, OBJECTS_BOUNDARIES_WIDTH, SIMULATION_WINDOW_HEIGHT), false) 
{
	SFMLApplicationSettings settings;
	settings.applicationName = "Expérience de collisions élastiques";
	settings.windowWidth = SIMULATION_WINDOW_WIDTH;
	settings.windowHeight = SIMULATION_WINDOW_HEIGHT;
	settings.backgroundColor = color_palette::VERY_DARK_GRAY;
	initApplication(settings);
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
	object_.updateDragAndDrop(event, mouse);
	launcher_.update(event, mouse);
}

void CollisionSimulationApp::update(float dt) {
}

void CollisionSimulationApp::customRender() {
	drawOnWindow(launcher_);
	drawOnWindow(object_);
}
