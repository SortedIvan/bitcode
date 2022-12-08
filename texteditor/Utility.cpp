#include "Utility.h"
#include <string>

bool Utility::RemoveLastCharFromString(std::string& line, int index) {
	if (line.size() != 0) {
		line.erase(index - 1, 1);
		//line.resize(line.size() - 1);
		return false;
	}
	return true;
}