#include "Utility.h"
#include <string>

bool Utility::RemoveLastCharFromString(std::string& line) {
	if (line.size() != 0) {
		line.resize(line.size() - 1);
		return false;
	}
	return true;
}