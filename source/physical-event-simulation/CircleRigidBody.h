#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>
#include "constants.h"
#include "color_palette.h"
#include <deque>
#include "Label.h"

// Représente un corps rigide circulaire à deux dimensions.
// Un corps rigide est simplement un corps physique ne pouvant pas se déformer.
// Cette classe est utilisée par les deux simulations pour représenter les projectiles.
// Hérite de sf::Drawable pour pouvoir être affiché sur une fenêtre SFML.
class CircleRigidBody : public sf::Drawable {
public:
	// Construit un projectile à partir d'un cercle (sa hitbox), d'une masse et d'une vitesse initiale.
	CircleRigidBody(ch::Circle circle = ch::Circle(), float mass = 0.f, ch::vec_t initialVelocity = ch::NULL_VEC);
	
	// Détecte et résoud une potentielle collision entre le projectile et les "murs" donnés.
	// Ici, le but est de garantir que le projectile reste à l'intérieur du rectangle donné.
	void collideWithWalls(ch::AABB enclosingWalls);

	// Accélère le projectile par le vecteur de vélocité donné. L'accélération est instantanée.
	void accelerate(ch::vec_t acceleration);

	// Déplace le projectile par la translation donnée.
	void move(ch::vec_t translationVector);

	// Met à jour la position du projectile en fonction de sa vitesse et du temps écoulé.
	void update(float dt);

	// Détecte et résoud une potentielle collision entre le projectile actuel et le projectile donné.
	// En cas de collision, les deux projectiles sont repositionnés et une accélération leur est appliquée.
	void collideWith(CircleRigidBody& other);

	// Retourne la hitbox du projectile.
	ch::Circle getCircle() const;

	// Calcule l'énergie cinétique actuellement contenue dans le projectile.
	float computeKineticEnergy() const;

	// Retourne la masse du projectile.
	float getMass() const;

	// Retourne le vecteur de vélocité du projectile.
	ch::vec_t getVelocity() const;
private:
	// Retourne l'inverse de la masse du projectile (= 1/m). Utile pour la résolution de collisions.
	float inverseMass() const;

	// Sauvegarde la position actuelle et met à jour la "trace" du projectile.
	void savePosition();

	// Méthode héritée de sf::Drawable. Affiche le projectile sur la fenêtre.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	// Hitbox du projectile
	ch::Circle circle_;

	// Vecteur de vélocité
	ch::vec_t vel_;

	// Masse du projectile.
	float mass_;

	// Trace du projectile : une queue de vecteurs représentant des positions.
	std::deque<ch::vec_t> trace_;

	// Temps écoulé depuis la dernière sauvegarde d'une position.
	float timeSinceLastTraceSave_;

	// Label affichant la masse du projectile.
	Label massLabel_;

	// Forme SFML représentant le projectile.
	sf::CircleShape shape_;
};

