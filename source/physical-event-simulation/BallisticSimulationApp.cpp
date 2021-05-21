#include "BallisticSimulationApp.h"

constexpr float SIMULATION_WINDOW_WIDTH = 1200.f;
constexpr float SIMULATION_WINDOW_HEIGHT = 500.f;

constexpr float LAUNCHER_WIDTH = 300.f;

constexpr float BUTTON_TOP_MARGIN = 20.f;
constexpr float BUTTON_WIDTH = 80.f;
constexpr float BUTTON_HEIGHT = 40.f;

constexpr float SCALE_MARGIN_BOTTOM = 30.f;
constexpr float SCALE_X_POS = SIMULATION_WINDOW_WIDTH / 2.f;
constexpr float SCALE_Y_POS = SIMULATION_WINDOW_HEIGHT - SCALE_MARGIN_BOTTOM;

constexpr float TARGET_RIGHT_MARGIN = 30.f;

constexpr float WINDPICKER_TOP_MARGIN = 30.f;
constexpr float WINDPICKER_RIGHT_MARGIN = 80.f;
constexpr float WINDPICKER_TEXT_VERTICAL_OFFSET = 20.f;
constexpr float WINDPICKER_X = SIMULATION_WINDOW_WIDTH - WINDPICKER_RIGHT_MARGIN - WINDPICKER_RADIUS_PX - TARGET_RIGHT_MARGIN;
constexpr float WINDPICKER_Y = WINDPICKER_TOP_MARGIN + WINDPICKER_RADIUS_PX;

const std::string TARGET_HIT_TEXT = "Cible atteinte !";
const std::string TARGET_MISSED_TEXT = "Raté...";
const std::string APPLICATION_TITLE = "Expérience de balistique - Lucas Charbonnier";

constexpr float RHO = 1.225f; // Densité de l'air, en kg/m^3, au niveau de la mer, à 15°C
constexpr float PI = ch::FLT_PI; // Alias d'une autre constante de PI
constexpr float SPHERE_DRAG_COEFFICIENT = 0.47f; // Coefficient de frottement des objets sphériques

BallisticSimulationApp::BallisticSimulationApp() :
	launcher_(ch::AABB({ 0.f,0.f }, { LAUNCHER_WIDTH, SIMULATION_WINDOW_HEIGHT }), PX_PER_METER_BALLISTIC, OBJECTS_RADIUS_BALLISTIC),
	launchSimulationButton_(ch::AABB(SIMULATION_WINDOW_WIDTH / 2.f - BUTTON_WIDTH / 2.f, BUTTON_TOP_MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT), TINY_TEXT, "---"),
	simulationRunning_(false),
	scale_({ SCALE_X_POS, SCALE_Y_POS }, PX_PER_METER_BALLISTIC),
	target_(SIMULATION_WINDOW_WIDTH - TARGET_RIGHT_MARGIN, SIMULATION_WINDOW_HEIGHT, TARGET_RAD * PX_PER_METER_BALLISTIC),
	windPicker_(ch::vec_t(WINDPICKER_X, WINDPICKER_Y))
{
	SFMLApplicationSettings settings;
	settings.applicationName = APPLICATION_TITLE;
	settings.windowWidth = SIMULATION_WINDOW_WIDTH;
	settings.windowHeight = SIMULATION_WINDOW_HEIGHT;
	settings.backgroundColor = color_palette::VERY_DARK_GRAY;
	initApplication(settings);

	ch::AABB windPickerZone = ch::collision::enclosingAABB(ch::Circle({ WINDPICKER_X, WINDPICKER_Y }, WINDPICKER_RADIUS_PX));
	windIntensityLabel_.init(ch::AABB(windPickerZone.pos + ch::vec_t(0.f, WINDPICKER_RADIUS_PX + WINDPICKER_TEXT_VERTICAL_OFFSET), windPickerZone.size), TINY_TEXT, "-");

	launchSimulationButton_.setTextColor(color_palette::DARK_TEXT);
	updateLaunchButtonText();
}

void BallisticSimulationApp::handleEvent(const sf::Event& event) {
	switch (event.type) {
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Space:
			switchSimulationMode();
		}
		break;
	case sf::Event::Closed:
		exitApplication();
		break;
	}

	updateWidgets(event, getMousePosOnWindow());
}

void BallisticSimulationApp::updateWidgets(const sf::Event& event, ch::vec_t mousePos) {
	launcher_.update(event, mousePos);

	if (launchSimulationButton_.checkForMouseRelease(mousePos, event)) {
		switchSimulationMode();
	}

	if (!simulationRunning_) {
		target_.updateDragAndDrop(event, mousePos);
		windPicker_.update(event, mousePos);
	}
}

void BallisticSimulationApp::update(float dt) {
	if (fadingText_ != nullptr) {
		fadingText_->update(dt);
		if (fadingText_->hasDisappeared()) {
			fadingText_ = nullptr;
		}
	}

	if (simulationRunning_) {
		if (target_.checkForCollision(*projectile_)) {
			switchSimulationMode();
			spawnFadingText(TARGET_HIT_TEXT);
		}
		else if (projectileIsOutOfBounds()) {
			switchSimulationMode();
			spawnFadingText(TARGET_MISSED_TEXT);
		}

		projectile_->accelerate(ch::vec_t(0.f, GRAVITY) * PX_PER_METER_BALLISTIC * dt);
		applyDragForce(dt);
		projectile_->update(dt);
	}
}

void BallisticSimulationApp::applyDragForce(float dt) {
	// On récupère la vélocité de l'air (vitesse et direction du vent) à partir du WindPicker
	ch::vec_t fluidVel = windPicker_.computeWindIntensityAndDirection();

	// Vélocité du projectile
	ch::vec_t projVel = projectile_->getVelocity() / PX_PER_METER_BALLISTIC;

	// Masse et rayon
	float m = projectile_->getMass();
	float r = OBJECTS_RADIUS_BALLISTIC;

	// Vélocité relative entre le fluide et le projectile
	float relativeVelocity = ch::vec_magnitude(fluidVel - projVel);

	// Calcul de l'accélération
	ch::vec_t acceleration = (RHO * PI * r * r * SPHERE_DRAG_COEFFICIENT * relativeVelocity * (fluidVel - projVel)) / (2.f * m);

	// Application de l'accélération. On multiplie par le pas de temps pour que l'accélération soit proportionnelle au temps écoulé
	projectile_->accelerate(acceleration * dt);
}

void BallisticSimulationApp::customRender() {
	drawOnWindow(launchSimulationButton_);

	drawOnWindow(target_);
	drawOnWindow(scale_);

	if (simulationRunning_) {
		drawOnWindow(*projectile_);
		
		drawOnWindow(windPicker_.buildWindArrow());
	}
	else {
		drawOnWindow(launcher_);
		drawOnWindow(windPicker_);
		drawOnWindow(windIntensityLabel_);
	}

	float windIntensity = ch::vec_magnitude(windPicker_.computeWindIntensityAndDirection());
	std::string windInfoText = "Vent : " + utils::float_to_fixed_string(windIntensity) + " m/s";
	windIntensityLabel_.setText(windInfoText);

	if (fadingText_ != nullptr)
		drawOnWindow(*fadingText_);
}

void BallisticSimulationApp::switchSimulationMode() {
	simulationRunning_ = !simulationRunning_;
	updateLaunchButtonText();

	if (simulationRunning_) {
		scale_.makeSemiTransparent();
		projectile_ = std::make_unique<CircleRigidBody>(launcher_.constructCircleRigidBody());
	}
	else {
		scale_.makeOpaque();
	}
}

void BallisticSimulationApp::updateLaunchButtonText() {
	launchSimulationButton_.setText(simulationRunning_ ? STOP_BUTTON_TEXT : LAUNCH_BUTTON_TEXT);
}

bool BallisticSimulationApp::projectileIsOutOfBounds() const {
	static const float VERTICAL_MARGIN = 5000.f;
	static const auto BOUNDS = ch::AABB(0.f, -VERTICAL_MARGIN, SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT + VERTICAL_MARGIN);

	return !ch::collision::aabb_contains(BOUNDS, projectile_->getCircle());
}

void BallisticSimulationApp::spawnFadingText(std::string text) {
	fadingText_ = std::make_unique<FadingText>(getWindowSize() / 2.f, text);
}
