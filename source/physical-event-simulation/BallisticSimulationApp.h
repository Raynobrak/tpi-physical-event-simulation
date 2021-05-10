#pragma once

#include "SFMLApplicationBase.h"
#include "ProjectileLauncher.h"
#include "color_palette.h"

class BallisticSimulationApp : public SFMLApplicationBase {
public:
	BallisticSimulationApp();
private:
	void handleEvent(sf::Event& event) override;
	void update(float dt) override;
	void customRender() override;
private:
	ProjectileLauncher launcher_;
};

