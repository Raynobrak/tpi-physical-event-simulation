#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>

// Représente un cercle que l'utilisateur peut déplacer avec la souris
// Hérite de sf::Drawable (pour l'affichage).
class DraggableCircle : public sf::Drawable {
public:
	// Construit une nouvelle instance à partir d'un cercle, d'un rectangle représentant la zone de déplacement et d'un booléen indiquant si l'objet est bloqué horizontalement.
	DraggableCircle(ch::Circle circle, ch::AABB boundaries, bool lockHorizontally = false);

	// Retourne la position du centre du cercle.
	ch::vec_t getCirclePos() const;

	// Retourne le cercle sous-jacent.
	ch::Circle getCircle() const;

	// Met à jour le glisser-déposer en fonction d'un événement et de la position de la souris.
	bool updateDragAndDrop(const sf::Event& event, ch::vec_t mousePosOnWindow);
	
	// Change la couleur de fond du cercle.
	void setFillColor(sf::Color newColor);

	// Change la couleur de la bordure du cercle.
	void setOutlineColor(sf::Color newColor);
protected:
	// Cercle sous-jacent.
	ch::Circle circle_;

	// Zone dans laquelle le cercle peut être déplacé.
	ch::AABB boundaries_;
private:
	// Retourne true si la position donné se trouve dans le cercle.
	bool isHovered(ch::vec_t mousePos) const;

	// Vérifie si la position donnée est valide (= dans les limites) et déplace le cercle si c'est le cas.
	void updatePosition(ch::vec_t newPos);

	// Affiche le widget
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	// Forme SFML affichée sur l'écran pour représenter le cercle.
	sf::CircleShape circleShape_;

	// True si le cercle est fixé sur un rail vertical, sinon false.
	bool lockedHorizontally_;

	// True si le cercle est en train d'être déplacé, sinon false.
	bool isDragging_;

	// Point de départ du drag&drop
	ch::vec_t dragOrigin_;
};

