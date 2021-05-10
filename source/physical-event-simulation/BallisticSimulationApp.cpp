#include "BallisticSimulationApp.h"

constexpr float SIMULATION_WINDOW_HEIGHT = 500.f;
constexpr float SIMULATION_WINDOW_WIDTH = 1200.f;

BallisticSimulationApp::BallisticSimulationApp() : launcher_(ch::AABB({ 0.f,0.f }, {300.f, SIMULATION_WINDOW_HEIGHT})) {
	SFMLApplicationSettings settings;
	settings.applicationName = "Expérience de balistique";
	settings.windowWidth = SIMULATION_WINDOW_WIDTH;
	settings.windowHeight = SIMULATION_WINDOW_HEIGHT;
	settings.backgroundColor = color_palette::VERY_DARK_GRAY;
	initApplication(settings);
}

void BallisticSimulationApp::handleEvent(sf::Event& event) {
	switch (event.type) {
	case sf::Event::KeyPressed:
		switch (event.key.code) {

		}
		break;
	case sf::Event::Closed:
		exitApplication();
		break;
	}
}

void BallisticSimulationApp::update(float dt) {
}

void BallisticSimulationApp::customRender() {
	drawOnWindow(launcher_);
}
