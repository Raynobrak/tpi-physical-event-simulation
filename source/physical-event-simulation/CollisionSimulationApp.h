#pragma once

#include "SFMLApplicationBase.h"
#include "ProjectileLauncher.h"
#include "DraggableCircle.h"
#include "color_palette.h"

class CollisionSimulationApp : public SFMLApplicationBase {
public:
	CollisionSimulationApp();
private:
	void handleEvent(sf::Event& event) override;
	void update(float dt) override;
	void customRender() override;
private:
	ProjectileLauncher launcher_;
	DraggableCircle object_;
	
};

