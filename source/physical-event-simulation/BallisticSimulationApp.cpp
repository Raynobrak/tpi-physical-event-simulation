#include "BallisticSimulationApp.h"

constexpr float SIMULATION_WINDOW_HEIGHT = 500.f;
constexpr float SIMULATION_WINDOW_WIDTH = 1200.f;

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
constexpr float WINDPICKER_X = SIMULATION_WINDOW_WIDTH - WINDPICKER_RIGHT_MARGIN - WINDPICKER_RADIUS - TARGET_RIGHT_MARGIN;
constexpr float WINDPICKER_Y = WINDPICKER_TOP_MARGIN + WINDPICKER_RADIUS;

BallisticSimulationApp::BallisticSimulationApp() :
	launcher_(ch::AABB({ 0.f,0.f }, { LAUNCHER_WIDTH, SIMULATION_WINDOW_HEIGHT }), PIXELS_PER_METER_IN_BALLISTIC_SIMULATION, OBJECTS_RADIUS_IN_METERS_IN_BALLISTIC_SIMULATION),
	launchSimulationButton_(ch::AABB(SIMULATION_WINDOW_WIDTH / 2.f - BUTTON_WIDTH / 2.f, BUTTON_TOP_MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT), TINY_TEXT_SIZE, "---"),
	simulationRunning_(false),
	scale_({ SCALE_X_POS, SCALE_Y_POS }, PIXELS_PER_METER_IN_BALLISTIC_SIMULATION),
	target_(SIMULATION_WINDOW_WIDTH - TARGET_RIGHT_MARGIN, SIMULATION_WINDOW_HEIGHT, TARGET_RADIUS_IN_METERS * PIXELS_PER_METER_IN_BALLISTIC_SIMULATION),
	windPicker_(ch::vec_t(WINDPICKER_X, WINDPICKER_Y))
{
	SFMLApplicationSettings settings;
	settings.applicationName = "Expérience de balistique - Lucas Charbonnier";
	settings.windowWidth = SIMULATION_WINDOW_WIDTH;
	settings.windowHeight = SIMULATION_WINDOW_HEIGHT;
	settings.backgroundColor = color_palette::VERY_DARK_GRAY;
	initApplication(settings);

	auto windPickerZone = ch::collision::enclosingAABB(ch::Circle({ WINDPICKER_X, WINDPICKER_Y }, WINDPICKER_RADIUS));
	windIntensityLabel_.init(ch::AABB(windPickerZone.pos + ch::vec_t(0.f, WINDPICKER_RADIUS + WINDPICKER_TEXT_VERTICAL_OFFSET), windPickerZone.size), TINY_TEXT_SIZE, "-");

	launchSimulationButton_.setTextColor(color_palette::DARK_TEXT);
	updateLaunchButtonText();
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

	auto mouse = getMousePosOnWindow();

	launcher_.update(event, mouse);

	if (launchSimulationButton_.checkForMouseRelease(mouse, event)) {
		switchSimulationMode();
	}

	if (!simulationRunning_) {
		target_.updateDragAndDrop(event, mouse);
		windPicker_.update(event, mouse);
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

		if (projectileIsOutOfBounds()) {
			switchSimulationMode();
			spawnFadingText(TARGET_MISSED_TEXT);
		}

		projectile_->accelerate(ch::vec_t(0.f, GRAVITY) * PIXELS_PER_METER_IN_BALLISTIC_SIMULATION * dt);
		applyDragForce(dt);
		projectile_->update(dt);
	}
}

void BallisticSimulationApp::applyDragForce(float dt) {
	auto fluidVelocity = windPicker_.computeWindIntensityAndDirection();

	auto projectileVelocity = projectile_->getVelocity() / PIXELS_PER_METER_IN_BALLISTIC_SIMULATION;
	auto mass = projectile_->getMass();
	auto radius = OBJECTS_RADIUS_IN_METERS_IN_BALLISTIC_SIMULATION;

	float relativeVelocity = ch::vec_magnitude(fluidVelocity - projectileVelocity);

	auto acceleration = (RHO * PI * radius * radius * SPHERE_DRAG_COEFFICIENT * relativeVelocity * (fluidVelocity - projectileVelocity)) / (2.f * mass);
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
	launchSimulationButton_.setText(simulationRunning_ ? LAUNCHER_STOP_BUTTON_TEXT : LAUNCHER_LAUNCH_BUTTON_TEXT);
}

bool BallisticSimulationApp::projectileIsOutOfBounds() const {
	static const float VERTICAL_MARGIN = 5000.f;
	static const auto BOUNDS = ch::AABB(0.f, -VERTICAL_MARGIN, SIMULATION_WINDOW_WIDTH, SIMULATION_WINDOW_HEIGHT + VERTICAL_MARGIN);

	return !ch::collision::aabb_contains(BOUNDS, projectile_->getCircle());
}

void BallisticSimulationApp::spawnFadingText(std::string text) {
	fadingText_ = std::make_unique<FadingText>(getWindowSize() / 2.f, text);
}
