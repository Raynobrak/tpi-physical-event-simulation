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

// Représente l'application qui gère la simulation de collisions.
// Hérite de SFMLApplicationBase car cette application nécessite l'affichage d'une fenêtre.
class CollisionSimulationApp : public SFMLApplicationBase {
public:
	// Constructeur par défaut
	CollisionSimulationApp();
private:
	// Traite l'événement donné.
	// Méthode héritée de SFMLApplicationBase
	void handleEvent(const sf::Event& event) override;

	// Met à jour les différents widgets de l'interface
	void updateWidgets(const sf::Event& event, ch::vec_t mousePos);

	// Met à jour la simulation en fonction du temps écoulé
	// Méthode héritée de SFMLApplicationBase
	void update(float dt) override;

	// Affiche l'application sur la fenêtre.
	// Méthode héritée de SFMLApplicationBase
	void customRender() override;

	// Met à jour le texte du bouton permettant de lancer/stopper la simulation.
	void updateLaunchButtonText();

	// Démarre ou stoppe la simulation (en fonction de son état actuel)
	void switchSimulationMode();

	// Ajoute des nouveaux objets à des positions aléatoires.
	void spawnRandomCircles();
private:
	// Lanceur de projectiles
	ProjectileLauncher launcher_;

	// Contient tous les ConfigurableCircle lorsque la simulation est arrêtée.
	std::vector<ConfigurableCircle> configurableCircles_;

	// Contient tous les projectiles de la simulation.
	std::vector<CircleRigidBody> circleRigidBodies_;

	// Bouton permettant de lancer/arrêter la simulation.
	Button launchSimulationButton_;

	// État de la simulation : true si elle est en cours, sinon false.
	bool simulationRunning_;

	// Icône permettant de visualiser l'échelle de la simulation.
	ScaleIcon scale_;
};

