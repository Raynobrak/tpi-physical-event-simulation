#include "MainMenuApplication.h"

constexpr float MAIN_MENU_WINDOW_WIDTH = 600.f;
constexpr float MAIN_MENU_WINDOW_HEIGHT = 450.f;
constexpr float BUTTONS_MARGINS = 120.f;
constexpr float BUTTONS_WIDTH = MAIN_MENU_WINDOW_WIDTH - 2 * BUTTONS_MARGINS;
constexpr float BUTTONS_HEIGHT = 70.f;

MainMenuApplication::MainMenuApplication() {
	auto settings = SFMLApplicationSettings();
	settings.windowWidth = MAIN_MENU_WINDOW_WIDTH;
	settings.windowHeight = MAIN_MENU_WINDOW_HEIGHT;
	settings.applicationName = "Menu principal - Physical Event Simulation";
	settings.fps = 60.f;
	settings.fixedTimeStep = 1.f / 30.f;
	settings.backgroundColor = color_palette::VERY_DARK_GRAY;

	initApplication(settings);

	menuTitle_.init({ 0.f,0.f,MAIN_MENU_WINDOW_WIDTH,100.f }, 60u, "Physical Event Simulation");

	collisionsSimButton_.init({ BUTTONS_MARGINS,120,BUTTONS_WIDTH,BUTTONS_HEIGHT }, 48u, "Collisions");
	collisionsSimButton_.setTextColor(color_palette::DARK_TEXT);

	ballisticSimButton_.init({ BUTTONS_MARGINS,210,BUTTONS_WIDTH,BUTTONS_HEIGHT }, 48u, "Balistique");
	ballisticSimButton_.setTextColor(color_palette::DARK_TEXT);

	leaveButton_.init({ BUTTONS_MARGINS + 60.f,MAIN_MENU_WINDOW_HEIGHT - BUTTONS_HEIGHT - 50.f,BUTTONS_WIDTH - 120.f,BUTTONS_HEIGHT }, 36u, "Quitter");
	leaveButton_.setTextColor(color_palette::DARK_TEXT);
}

void MainMenuApplication::handleEvent(sf::Event& event) {
	switch (event.type) {
	case sf::Event::Closed:
		exitApplication();
		break;
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			exitApplication();
			break;
		}
		break;
	}

	if (collisionsSimButton_.checkForMouseRelease(getMousePosOnWindow(), event)) {
		closeWindow();
		CollisionSimulationApp app;
		app.run();
		showWindow();
	}

	if (ballisticSimButton_.checkForMouseRelease(getMousePosOnWindow(), event)) {
		closeWindow();
		BallisticSimulationApp app;
		app.run();
		showWindow();
	}

	if (leaveButton_.checkForMouseRelease(getMousePosOnWindow(), event)) {
		exitApplication();
	}
}

void MainMenuApplication::update(float dt) {

}

void MainMenuApplication::customRender() {
	drawOnWindow(menuTitle_);

	drawOnWindow(collisionsSimButton_);
	drawOnWindow(ballisticSimButton_);
	drawOnWindow(leaveButton_);
}
