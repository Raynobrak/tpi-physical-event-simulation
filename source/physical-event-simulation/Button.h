#pragma once

#include "Label.h"

// Représente un bouton.
// Le bouton est déclenché lorsque le bouton de la souris est relâché. Cela peut être détecté à l'aide de la méthode checkForMouseRelease().
// Hérite de sf::Drawable pour pouvoir être affichable sur une fenêtre SFML.
class Button : public sf::Drawable {
public:
	// Constructeur par défaut
	Button();

	// Construit un bouton à partir d'une AABB (un rectangle), d'une taille de police et d'un texte à afficher.
	Button(ch::AABB clickableZone, unsigned characterSize, std::string text);

	// Permet d'initialiser un bouton après coup si jamais il a été construit par défaut.
	void init(ch::AABB clickableZone, unsigned characterSize, std::string text);

	// Met à jour l'état du bouton et vérifie si l'événement donné ainsi que la position de la souris indiquent qu'il a été déclenché.
	// Le bouton est déclenché lorsque le bouton a été cliqué et que le bouton de la souris est relâché lorsque la souris survole le bouton.
	bool checkForMouseRelease(ch::vec_t mousePos, sf::Event event);

	// Retourne true si la position donnée se trouve dans la zone du bouton, sinon false.
	bool isHovered(ch::vec_t mousePos) const;

	// Permet de changer le texte affiché sur le bouton.
	void setText(std::string newText);

	// Définit la couleur du texte du bouton.
	void setTextColor(sf::Color newColor);
private:
	// Méthode héritée de la classe abstraite sf::Drawable. Affiche le bouton sur la cible de rendu donnée.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	// Label qui sera affiché sur le bouton.
	Label buttonLabel_;

	// État du bouton : Est-ce qu'il est actuellement pressé ?
	bool isClicked_;
};

