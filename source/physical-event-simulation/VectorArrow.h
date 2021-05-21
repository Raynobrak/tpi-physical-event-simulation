#pragma once

#include <SFML/Graphics.hpp>
#include <charbrary.h>

const sf::Color DEFAULT_ARROW_COLOR = sf::Color::White;

// Widget représentant un vecteur, c'est à dire, une flèche avec une longueur, une direction et un point d'origine.
// Hérite de sf::Drawable pour permettre l'affichage sur une fenêtre.
class VectorArrow : public sf::Drawable {
public:
	// Construit une nouvelle flèche à partir de la valeur du vecteur sous-jacent, de son point de départ et de sa couleur.
	VectorArrow(ch::vec_t value = ch::NULL_VEC, ch::vec_t origin = ch::NULL_VEC, sf::Color color = DEFAULT_ARROW_COLOR);

	// Redéfinit la valeur du vecteur sous-jacent
	void setLength(ch::vec_t newLength);

	// Redéfinit le point de départ de la flèche.
	void setOrigin(ch::vec_t newOrigin);
private:
	// Affiche la flèche sur la cible de rendu donnée.
	// Méthode héritée de sf::Drawable.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	// Point de départ
	ch::vec_t origin_;

	// Vecteur représentant la flèche.
	ch::vec_t length_;

	// Couleur de la flèche
	sf::Color color_;
};

