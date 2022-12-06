#include "Utility.h"
#include <string>

Utility::RemoveLastCharFromString(std::string& line) {
	line.resize(current_line.size() - 1);
}