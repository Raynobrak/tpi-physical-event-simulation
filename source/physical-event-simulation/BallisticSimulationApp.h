#pragma once

#include "SFMLApplicationBase.h"
#include "ProjectileLauncher.h"
#include "color_palette.h"
#include "Button.h"
#include "ScaleIcon.h"
#include "TargetSlider.h"
#include "CircleRigidBody.h"
#include "FadingText.h"
#include "WindPicker.h"
#include "VectorArrow.h"
#include "utils.h"

// Représente l'application qui gère la simulation de balistique.
// Hérite de SFMLApplicationBase car cette application nécessite l'affichage d'une fenêtre.
class BallisticSimulationApp : public SFMLApplicationBase {
public:
	// Constructeur par défaut
	BallisticSimulationApp();
private:
	// Traite l'événement donné
	// Méthode héritée de SFMLApplicationBase
	void handleEvent(const sf::Event& event) override;

	// Met à jour les différents widgets de l'interface
	void updateWidgets(const sf::Event& event, ch::vec_t mousePos);

	// Met à jour l'application en fonction du pas de temps donné
	// Méthode héritée de SFMLApplicationBase
	void update(float dt) override;

	// Met à jour les forces de frottement s'appliquant sur le projectile
	void applyDragForce(float dt);

	// Affiche la simulation sur la fenêtre.
	// Méthode héritée de SFMLApplicationBase
	void customRender() override;

	// Démarre ou stoppe la simulation (en fonction de son état actuel)
	void switchSimulationMode();

	// Met à jour le texte du bouton permettant de lancer/arrêter la simulation
	void updateLaunchButtonText();

	// Retourne true si le projectile est en dehors des limites, sinon false.
	bool projectileIsOutOfBounds() const;

	// Affiche un message au milieu de l'écran qui va progressivement disparaître.
	void spawnFadingText(std::string text);
private:
	// Lanceur de projectile
	ProjectileLauncher launcher_; 

	// Bouton de démarrage/arrêt de la simulation
	Button launchSimulationButton_; 

	// État de la simulation (en cours/arrêtée). True si la simulation est en cours.
	bool simulationRunning_;

	// Un pointeur vers le projectile.
	// Lorsque le projectile existe, le pointeur pointera vers une instance de projectile, sinon, il aura la valeur nullptr.
	std::unique_ptr<CircleRigidBody> projectile_;

	// Un pointeur vers le potentiel texte à afficher au milieu de l'écran.
	// Étant donné qu'un FadingText est inévitablement voué à disparaître (par définition), un pointeur est utilisé pour
	// permettre de représenter le cas où il n'y a pas (ou plus) de texte à afficher.
	std::unique_ptr<FadingText> fadingText_;

	// Icône affichant l'échelle de la simulation avec une légende.
	ScaleIcon scale_;

	// Cible dont la position peut être modifiée par l'utilisateur.
	TargetSlider target_;

	// Widget permettant à l'utilisateur de sélectionner l'intensité et la direction du vent
	WindPicker windPicker_;

	// Label affichant l'intensité du vent
	Label windIntensityLabel_;
};

