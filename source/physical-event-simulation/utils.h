#pragma once

#include <string>

namespace utils {
	// Convertir un float en string en fonction d'un nombre de chiffres après la virgule à afficher.
	std::string float_to_fixed_string(float real, int digits = 2);
}
