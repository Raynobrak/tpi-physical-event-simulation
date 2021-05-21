#pragma once

#include "color_palette.h"
#include <SFML/Graphics.hpp>
#include "Label.h"

// Représente une échelle.
// Consiste simplement en l'affichage d'une distance ainsi que d'un label donnant la valeur de cette distance.
// Cette classe est utilisée pour afficher la distance prise par un mètre dans les simulations.
// Hérite de sf::Drawable pour pouvoir être affiché sur une fenêtre.
class ScaleIcon : public sf::Drawable {
public:
	// Construit une nouvelle échelle à partir d'une position centrale et du nombre de pixels dans un mètre.
	ScaleIcon(ch::vec_t center, float pixelsPerMeter);

	// Change la couleur de l'échelle pour qu'elle soit totalement opaque.
	void makeOpaque();

	// Change la couleur de l'échelle pour qu'elle soit semi-transparente.
	void makeSemiTransparent();
private:
	// Affiche l'échelle sur la fenêtre donnée.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
private:
	// Couleur actuelle de l'échelle.
	sf::Color currentColor_;

	// Label affichant la distance en mètres.
	Label label_;

	// Zone prise par l'échelle (sans compter le label qui, lui, est décalé vers le haut).
	ch::AABB zone_;
};

