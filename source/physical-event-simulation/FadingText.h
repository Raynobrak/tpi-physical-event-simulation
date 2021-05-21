#pragma once

#include "Label.h"

constexpr float DEFAULT_FADING_TIME = 3.f;

// Un FadingText est un label dont l'opacité diminue avec le temps.
// Cette classe est utilisée pour afficher un message lorsque la cible de la simulation de balistique est atteinte (ou non).
// Elle hérite donc de Label.
class FadingText : public Label {
public:
	// Construit un nouveau FadingText en fonction de sa position centrale, du texte à afficher et
	// du temps nécessaire à sa disparition totale.
	FadingText(ch::vec_t center, std::string text, float fadingTime = DEFAULT_FADING_TIME);

	// Met à jour l'opacité du texte en fonction du temps écoulé depuis la dernière mise à jour.
	void update(float dt);

	// Retourne true si le texte a totalement disparu. Permet de savoir si l'objet peut être supprimé.
	bool hasDisappeared() const;
private:
	// Temps restant avant la disparition totale du texte.
	float timeLeft_;
	
	// Durée totale pendant laquelle le texte est affiché.
	float fadingTime_;
};

