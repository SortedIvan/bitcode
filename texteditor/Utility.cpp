#include "Utility.h"
#include <string>

void Utility::RemoveLastCharFromString(std::string& line) {
	if (line.size() != 0) {
		line.resize(line.size() - 1);
	}
}