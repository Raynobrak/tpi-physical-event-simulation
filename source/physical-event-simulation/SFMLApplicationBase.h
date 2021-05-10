#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

struct SFMLApplicationSettings {
	std::string applicationName = "SFML Application";
	unsigned windowWidth = DEFAULT_WINDOW_WIDTH;
	unsigned windowHeight = DEFAULT_WINDOW_HEIGHT;
	float fps = DEFAULT_FPS;
	float fixedTimeStep = DEFAULT_FIXED_TIME_STEP;
	sf::Color backgroundColor = sf::Color::Black;

private:
	static constexpr unsigned DEFAULT_WINDOW_WIDTH = 400;
	static constexpr unsigned DEFAULT_WINDOW_HEIGHT = 300;
	static constexpr float DEFAULT_FPS = 60.f;
	static constexpr float DEFAULT_FIXED_TIME_STEP = 0.5f / DEFAULT_FPS;
};

class SFMLApplicationBase {
public: 
	void initApplication(SFMLApplicationSettings settings = SFMLApplicationSettings());
	void run();
protected: 
	virtual void update(float dt) = 0;
	sf::Vector2f getMousePosOnWindow() const;
	sf::Vector2f getWindowSize() const;
	void exitApplication();
	void closeWindow();
	void showWindow();
	void drawOnWindow(const sf::Drawable& d, const sf::RenderStates states = sf::RenderStates::Default);

	sf::RenderWindow window_;
private: 
	virtual void handleEvent(sf::Event& event);
	void render();
	virtual void customRender();
	
private:
	sf::Color windowClearColor_;
	float fixedTimeStep_;
	float fps_;
	bool exitApplication_;
	SFMLApplicationSettings originalSettings_;
};

