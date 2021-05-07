#include "SFMLApplicationBase.h"

void SFMLApplicationBase::initApplication(SFMLApplicationSettings settings) {
	window_.create({ settings.windowWidth, settings.windowHeight }, settings.applicationName);

	windowClearColor_ = settings.backgroundColor;
	fixedTimeStep_ = settings.fixedTimeStep;
	fps_ = settings.fps;
}

void SFMLApplicationBase::run() {
	sf::Clock updateClock;
	sf::Clock renderClock;
	sf::Event event;

	float timeBetweenFrames = 1.f / fps_;

	while (window_.isOpen()) {
		while (window_.pollEvent(event)) {
			handleEvent(event);
		}

		if (updateClock.getElapsedTime().asSeconds() >= fixedTimeStep_) {
			updateClock.restart();
			update(fixedTimeStep_);
		}

		if (renderClock.getElapsedTime().asSeconds() >= timeBetweenFrames) {
			renderClock.restart();
			render();
		}
	}
}

sf::Vector2f SFMLApplicationBase::getMousePosOnWindow() const {
	return sf::Vector2f(sf::Mouse::getPosition(window_));
}

sf::Vector2f SFMLApplicationBase::getWindowSize() const {
	return sf::Vector2f(window_.getSize());
}

void SFMLApplicationBase::exitApplication() {
	window_.close();
}

void SFMLApplicationBase::drawOnWindow(const sf::Drawable& d, const sf::RenderStates states) {
	window_.draw(d, states);
}

void SFMLApplicationBase::handleEvent(sf::Event& event) {}

void SFMLApplicationBase::render() {
	window_.clear(windowClearColor_);
	customRender();
	window_.display();
}

void SFMLApplicationBase::customRender() {}
