#include "SFMLApplicationBase.h"
#include "get_application_icon_image.h"

void SFMLApplicationBase::initApplication(SFMLApplicationSettings settings) {
	window_.create({ settings.windowWidth, settings.windowHeight }, settings.applicationName, sf::Style::Titlebar | sf::Style::Close);

	windowClearColor_ = settings.backgroundColor;
	fixedTimeStep_ = settings.fixedTimeStep;
	fps_ = settings.fps;
	exitApplication_ = false;
	originalSettings_ = settings;

	setWindowIcon();
}

void SFMLApplicationBase::run() {
	// Chronomètres pour la mise à jour et le rendu de l'application.
	sf::Clock updateClock;
	sf::Clock renderClock;

	sf::Event event;

	float timeBetweenFrames = 1.f / fps_;

	// Boucle principale : tant que l'application ne doit pas fermer...
	while (!exitApplication_) {
		// Tant que la fenêtre est ouverte...
		while (window_.isOpen()) {
			// Si le temps écoulé depuis la dernière mise à jour dépasse le timestep...
			if (updateClock.getElapsedTime().asSeconds() >= fixedTimeStep_) {
				// Gestion des événements
				while (window_.pollEvent(event)) {
					handleEvent(event);
				}

				updateClock.restart();

				// Mise à jour de l'application
				update(fixedTimeStep_);
			}

			// Si le temps écoulé depuis le dernier affichage dépasse le temps entre chaque frame...
			if (renderClock.getElapsedTime().asSeconds() >= timeBetweenFrames) {
				renderClock.restart();

				// Affichage
				render();
			}
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
	closeWindow();
	exitApplication_ = true;
}

void SFMLApplicationBase::closeWindow() {
	window_.close();
}

void SFMLApplicationBase::showWindow() {
	initApplication(originalSettings_);
}

void SFMLApplicationBase::drawOnWindow(const sf::Drawable& d, const sf::RenderStates states) {
	window_.draw(d, states);
}

void SFMLApplicationBase::setWindowIcon() {
	auto& icon = get_application_icon_image();
	auto size = icon.getSize();
	window_.setIcon(size.x, size.y, icon.getPixelsPtr());
}

void SFMLApplicationBase::render() {
	window_.clear(windowClearColor_);
	customRender();
	window_.display();
}