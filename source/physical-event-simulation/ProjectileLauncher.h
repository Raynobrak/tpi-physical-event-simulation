#pragma once

#include <SFML/Graphics.hpp>
#include "Label.h"
#include "DraggableCircle.h"
#include "LauncherSling.h"
#include "constants.h"
#include "CircleRigidBody.h"

// Représente le lanceur de projectile. Le lanceur est une partie de l'interface graphique permettant de
// positionner le futur projectile, de spécifier la direction et la vitesse de départ et de visualiser ces données.
// Hérite de sf::Drawable pour pouvoir être affiché sur une fenêtre.
class ProjectileLauncher : public sf::Drawable {
public:
	// Construit le lanceur à partir de la zone cliquable, du nombre de pixels par mètre et du rayon du projectile en mètres.
	ProjectileLauncher(ch::AABB zone, float pixelsPerMeter, float projectileRadiusInMeters);

	// Met à jour le lanceur pour prendre en compte les nouveaux événements.
	void update(const sf::Event& event, ch::vec_t mousePosOnWindow);

	// Construit le futur projectile à partir de l'état actuel du lanceur.
	CircleRigidBody constructCircleRigidBody() const;
private:
	// Met à jour le label montrant les propriétés du futur projectile.
	void updateInformations();

	// Affiche le lanceur sur la fenêtre donnée.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	// Label montrant les propriétés du futur projectile.
	Label topLeftInformations_;

	// Forme SFML représentant la zone cliquable du lanceur. 
	sf::RectangleShape zone_;

	// Un cercle que l'on peut drag&drop représentant le futur projectile.
	DraggableCircle projectile_;

	// Partie "catapulte" du lanceur. Gère la position du bras de lancement.
	LauncherSling sling_;
	
	// Masse du futur projectile.
	float projectileMass_;

	// Valeur permettant la conversion de pixels en mètres et inversement.
	float pixelsPerMeter_;
};

