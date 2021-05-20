#pragma once

#include "SFMLApplicationBase.h"
#include "ProjectileLauncher.h"
#include "color_palette.h"
#include "Button.h"
#include "ScaleIcon.h"
#include "TargetSlider.h"
#include "CircleRigidBody.h"
#include "FadingText.h"
#include "WindPicker.h"
#include "VectorArrow.h"
#include "utils.h"

class BallisticSimulationApp : public SFMLApplicationBase {
public:
	BallisticSimulationApp();
private:
	void handleEvent(sf::Event& event) override;
	void update(float dt) override;
	void applyDragForce(float dt);
	void customRender() override;
	void switchSimulationMode();
	void updateLaunchButtonText();
	bool projectileIsOutOfBounds() const;

	void spawnFadingText(std::string text);
private:
	ProjectileLauncher launcher_;

	Button launchSimulationButton_;
	bool simulationRunning_;

	std::unique_ptr<CircleRigidBody> projectile_;
	std::unique_ptr<FadingText> fadingText_;

	ScaleIcon scale_;
	TargetSlider target_;
	WindPicker windPicker_;
	Label windIntensityLabel_;
};

