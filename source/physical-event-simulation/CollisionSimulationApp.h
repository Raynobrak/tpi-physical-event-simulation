#pragma once

#include "SFMLApplicationBase.h"
#include "ProjectileLauncher.h"
#include "DraggableCircle.h"
#include "color_palette.h"
#include "Button.h"
#include "CircleRigidBody.h"
#include "ConfigurableCircle.h"
#include "utils.h"
#include "ScaleIcon.h"

class CollisionSimulationApp : public SFMLApplicationBase {
public:
	CollisionSimulationApp();
private:
	void handleEvent(sf::Event& event) override;
	void update(float dt) override;
	void customRender() override;
	void updateLaunchButtonText();
	void switchSimulationMode();
	void spawnRandomCircles();
private:
	ProjectileLauncher launcher_;

	std::vector<ConfigurableCircle> configurableCircles_;
	std::vector<CircleRigidBody> circleRigidBodies_;

	Button launchSimulationButton_;
	bool simulationRunning_;

	ScaleIcon scale_;
};

