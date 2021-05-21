#pragma once

#include <SFML/Graphics.hpp>
#include "CircleRigidBody.h"
#include "DraggableCircle.h"
#include "Label.h"

// Représente un cercle configurable.
// Les propriétés d'un cercle configurable sont sa masse (qui peut être modifiée à l'aide de la molette
// de la souris) et sa position (que l'on peut changer en glissant-déposant le cercle).
//
// Concrètement, un cercle configurable est un widget permettant à l'utilisateur de configurer un futur CircleRigidBody.
//
// Hérite de DraggableCircle pour gérer le drag&drop.
class ConfigurableCircle : public DraggableCircle {
public:
	// Construit un nouveau cercle configurable à partir d'une hitbox, de ses limites (la zone dans laquelle
	// le cercle peut être déplacé) et de sa masse de départ.
	ConfigurableCircle(ch::Circle circle, ch::AABB boundaries, float defaultMass = 1.f);

	// Met à jour l'objet en fonction d'un événement qui s'est produit et de la position de la souris.
	// Si la position est modifiée, cette méthode retourne true, sinon false.
	bool update(const sf::Event& event, ch::vec_t mousePosOnWindow);

	// Retourne la hitbox du cercle.
	ch::Circle getCircle() const;

	// Construit un nouveau corps physique à partir de la configuration actuelle.
	CircleRigidBody constructCircleRigidBody() const;
private:
	// Méthode héritée de sf::Drawable (dont DraggableCircle hérite elle-même). Affiche le cercle et ses propriétés sur la cible de rendu donné.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	// Masse du futur corps physique
	float mass_;

	// Label affichant la masse.
	Label massLabel_;
};

