#include "utils.h"

#include <cmath>
#include <sstream>

std::string utils::float_to_fixed_string(float real, int digits) {
	std::stringstream stream;
	stream.precision(digits);
	stream << std::fixed;
	stream << real;

	auto str = stream.str();
	if (str == "-0.00")
		str = "0.00";

	return str;
}