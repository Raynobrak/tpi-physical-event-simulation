#pragma once

#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>

namespace utils {
	// Convertit un float en string en fonction d'un nombre de chiffres après la virgule à afficher.
	std::string float_to_fixed_string(float real, int digits = 2);

	// Fonction libre permettant d'obtenir une référence vers une police d'écriture.
	// L'objet retourné est une référence vers une sf::Font de la SFML.
	const sf::Font& get_default_font();

	// Retourne une référence constante vers une sf::Image statique contenant l'icône de l'application.
	const sf::Image& get_application_icon_image();
}
