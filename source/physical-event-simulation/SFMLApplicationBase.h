#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

#include "SFMLApplicationSettings.h"

// Classe de base abstraite pouvant être utilisée pour les applications comportant une fenêtre.
// Le but de cette classe est d'encapsuler la boucle principale de l'application ainsi que le fonctionnement d'une fenêtre SFML.
class SFMLApplicationBase {
public: 
	// Initialise l'application avec les paramètres donnés.
	void initApplication(SFMLApplicationSettings settings = SFMLApplicationSettings());

	// Lance l'application
	void run();
protected: 
	// Méthode virtuelle pure (devant être surchargée dans les classes dérivées).
	// Les surcharges devront s'occuper de mettre à jour l'application en fonction du pas de temps.
	virtual void update(float dt) = 0;

	// Méthode utilitaire permettant d'obtenir la position de la souris par rapport à l'origine (le coin haut-gauche) de la fenêtre.
	sf::Vector2f getMousePosOnWindow() const;

	// Retourne la taille de la fenêtre sous forme d'un vecteur.
	sf::Vector2f getWindowSize() const;

	// Quitte l'application.
	void exitApplication();

	// Ferme la fenêtre sans quitter l'application.
	void closeWindow();

	// Affiche la fenêtre si ce n'était pas déjà le cas.
	void showWindow();

	// Méthode utilitaire permettant d'afficher un sf::Drawable sur la fenêtre.
	void drawOnWindow(const sf::Drawable& d, const sf::RenderStates states = sf::RenderStates::Default);

	// Change l'icône de la fenêtre
	void setWindowIcon();

	// Fenêtre SFML sous-jacente.
	sf::RenderWindow window_;
private: 
	// Méthode virtuelle appellée lorsque un événement est détecté.
	virtual void handleEvent(const sf::Event& event) = 0;

	// Efface la fenêtre, appelle customRender() et affiche la fenêtre.
	void render();

	// Méthode virtuelle pure (devant être surchargées dans les classes dérivées) qui devra contenir les appels à la méthode drawOnWindow().
	virtual void customRender() = 0;
	
private:
	// Background de la fenêtre
	sf::Color windowClearColor_;

	// Pas de temps séparant chaque frame et avec laquel l'application est mise à jour.
	float fixedTimeStep_;

	// Nombre de rafraîchissements de la fenêtre par secondes.
	float fps_;

	// Indique si l'application doit s'arrêter. Si vrai, la boucle principale sera quitté lors de la prochain vérification.
	bool exitApplication_;

	// Paramètres initiaux donnés lors de la création de l'application.
	SFMLApplicationSettings originalSettings_;
};

