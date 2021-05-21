#pragma once

#include "SFMLApplicationBase.h"
#include "CollisionSimulationApp.h"
#include "BallisticSimulationApp.h"

#include "Label.h"
#include "Button.h"

// Représente l'application qui gère le menu principal.
// Hérite de SFMLApplicationBase car cette application nécessite l'affichage d'une fenêtre.
class MainMenuApplication : public SFMLApplicationBase {
public:
	// Constructeur par défaut
	MainMenuApplication();
private:
	// Traite l'événement donné
	void handleEvent(const sf::Event& event) override;

	// Met à jour l'application en fonction du temps écoulé depuis la dernière mise à jour.
	void update(float dt) override;

	// Affiche l'application
	void customRender() override;
private:
	// Label pour le titre principal
	Label menuTitle_;

	// Bouton permettant d'ouvrir la simulation de collisions.
	Button collisionsSimButton_;

	// Bouton permettant d'ouvrir la simulation de balistique.
	Button ballisticSimButton_;

	// Bouton permettant de quitter le programme.
	Button leaveButton_;
};

