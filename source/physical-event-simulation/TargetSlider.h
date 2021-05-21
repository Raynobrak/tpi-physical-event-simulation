#pragma once

#include "DraggableCircle.h"
#include "CircleRigidBody.h"

// Représente la cible dans la simulation de balistique.
// Permet à l'utilisateur de drag&drop la cible pour changer sa hauteur.
class TargetSlider : public DraggableCircle {
public:
	// Construit une nouvelle cible à partir de la position horizontale, de la hauteur de la zone d'édition et du rayon de la cible.
	TargetSlider(float xPos, float height, float targetRadius);

	// Met à jour le drag&drop en fonction de l'événement survenu ainsi que de la position de la souris sur la fenêtre.
	void update(sf::Event event, ch::vec_t mousePos);

	// Retourne true si le projectile donné est en collision avec la cible.
	bool checkForCollision(const CircleRigidBody& body) const;
private:
	// Affiche la cible sur la fenêtre donnée.
	// Méthode héritée de sf::Drawable (dont DraggableCircle hérite) permettant l'affichage sur une fenêtre.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	// "rail" sur lequel la cible peut se déplacer.
	sf::VertexArray sliderRail_;
};

