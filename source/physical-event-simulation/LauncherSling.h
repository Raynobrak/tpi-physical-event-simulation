#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>
#include "DraggableCircle.h"
#include "color_palette.h"
#include "constants.h"

// Le LauncherSling est un partie du ProjectileLauncher correspondant à la partie "catapulte" du lancuer.
// Concrètement, cette classe permet de gérer le drag&drop du bras de lancement ainsi que de calculer
// la vitesse et la direction du lancer.
// Hérite de sf::Drawable pour pouvoir être affiché sur une cible de rendu SFML.
class LauncherSling : public sf::Drawable {
public:
	// Construit une nouvelle "catapulte" à partir des limites dans laquelle le bras peut être déplacé, du DraggableCircle représentant
	// le projectile et du nombre de pixels contenus dans un mètre (servira pour la conversion en m/s).
	LauncherSling(ch::AABB zone, const DraggableCircle& circle, float pixelsPerMeter);

	// Met à jour le drag&drop à partir d'un événement qui s'est produit et de la position de la souris.
	void updateDragAndDrop(const sf::Event& event, ch::vec_t mousePosOnWindow);

	// Retourne un vecteur unitaire représentant la direction du projectile.
	ch::vec_t getProjectileDirection() const;

	// Retourne la vitesse du projectile au lancer en mètres par seconde.
	float getProjectileInitialVelocityInMetersPerSecond() const;

	// Retourne true si le projectile est survolé avec la souris.
	bool isProjectileHovered(ch::vec_t mousePos) const;
private:
	// Met à jour la position du bras de lancement.
	void updatePosition(ch::vec_t newPos);
private:
	// Forme SFML représentant le bout du bras de lancement.
	sf::RectangleShape rectShape_;

	// Bout du bras de lancement : un rectangle.
	ch::AABB rect_;

	// Limites dans laquelle le bras de lancement peut être déplacé.
	ch::AABB boundaries_;

	// Référence constante vers le projectile duquel le bras de lancement part.
	const DraggableCircle& projectile_;

	// Affiche le bras de lancement sur la cible de rendu donnée.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Valeur permettant la conversion de pixels en mètres
	float pixelsPerMeter_;
};

