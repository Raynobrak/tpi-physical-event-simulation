#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>

#include <iostream>

#include "color_palette.h"

// Représente un label, c'est à dire un texte pouvant être affiché sur une fenêtre (d'où l'héritage de sf::Drawable).
// Cette classe Label a pour but d'améliorer et d'étendre les fonctionnalités de la classe sf::Text de la SFML.
// Par exemple, Label va automatiquement centrer le texte au sein d'une zone (AABB), chose qui est parfois compliqué avec sf::Text.
class Label : public sf::Drawable {
public:
	// Constructeur par défaut
	Label();

	// Construit un nouveau label à partir d'un rectangle au sein duquel il sera centré, d'une taille de police et d'un texte à afficher.
	Label(ch::AABB zone, unsigned characterSize, std::string text);

	// Initialise le Label après sa construction. Utile si l'objet a été construit par défaut.
	void init(ch::AABB zone, unsigned characterSize, std::string text);

	// Définit le texte affiché par le label.
	void setText(std::string str);

	// Définit la position du coin haut-gauche de la zone contenant le Label.
	void setPosition(ch::vec_t newPos);

	// Définit la couleur de remplissage du texte.
	void setTextColor(sf::Color newColor);

	// Retourne la zone du label, c'est à dire, une AABB.
	ch::AABB getZone() const;
private:
	// Affiche le Label sur la cible de rendu donnée
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Centre le texte au sein de la zone. Cette méthode doit être appellée lorsque la position du texte est changée.
	void centerText();

	// Zone invisible et conceptuelle englobant le texte et au sein de laquelle il est centré verticalement et horizontalement.
	ch::AABB textZone_;

	// Objet sous-jacent de la SFML permettant d'afficher du texte à l'écran.
	sf::Text text_;
};

