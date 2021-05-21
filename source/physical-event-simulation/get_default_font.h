#pragma once

#include <SFML/Graphics/Font.hpp>

// Fonction libre permettant d'obtenir une référence vers une police d'écriture.
// L'objet retourné est une référence vers une sf::Font de la SFML.
const sf::Font& get_default_font();

