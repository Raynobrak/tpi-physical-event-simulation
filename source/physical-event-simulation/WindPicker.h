#pragma once

#include "Label.h"
#include "VectorArrow.h"

constexpr float WINDPICKER_RADIUS_PX = 80.f;
constexpr float MAX_WIND_SPEED = 50.f;

// Widget circulaire permettant de choisir la direction et l'intensité du vent à l'aide de la souris.
// Hérite de sf::Drawable pour pouvoir être affiché sur une fenêtre.
class WindPicker : public sf::Drawable {
public:
	// Construit un nouveau WindPicker en fonction de sa position centrale.
	WindPicker(ch::vec_t center);

	// Calcule le vecteur de vélocité du vent à partir du point sélectionné avec la souris.
	ch::vec_t computeWindIntensityAndDirection() const;

	// Vérifie si l'utilisateur a intéragi avec le widget.
	void update(sf::Event event, ch::vec_t mousePos);

	// Construit une flèche permettant de visualiser le vecteur de vélocité du vent.
	VectorArrow buildWindArrow() const;
private:
	// Affiche le WindPicker sur la cible de rendu donnée.
	// Méthode héritée de sf::Drawable.
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
private:
	// Hitbox de la zone avec laquelle l'utilisateur peut intéragir.
	ch::Circle clickableZone_;

	// Point sélectionné par l'utilisateur au sein de la zone cliquable. Bout de la flèche.
	ch::vec_t selectedPoint_;

	// Retourne true si l'utilisateur est en train de modifier la position du bout de la flèche.
	bool isDragging_;
};

