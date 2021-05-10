#pragma once

#include "SFMLApplicationBase.h"
#include "CollisionSimulationApp.h"
#include "BallisticSimulationApp.h"

#include "Label.h"
#include "Button.h"

class MainMenuApplication : public SFMLApplicationBase {
public:
	MainMenuApplication();

private:
	void handleEvent(sf::Event& event) override;
	void update(float dt) override;
	void customRender() override;
private:
	Label menuTitle_;
	Button collisionsSimButton_;
	Button ballisticSimButton_;
	Button leaveButton_;
};

