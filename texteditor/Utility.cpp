#include "Utility.h"
#include <string>
using namespace std::literals::string_literals;

bool Utility::RemoveLastCharFromString(std::string& line, int index) {
	if (line.size() != 0) {
		line.erase(index - 1, 1);
		return false;
	}
	return true;
}

std::string Utility::MatchStringToRegex(std::regex regexpr, std::string string_to_match) {
	std::string found;
	std::smatch m;
	std::regex_search(string_to_match, m, regexpr);

	for (auto character : m) {
		found += character.str();
	}
	return found;
}

std::string Utility::MathPathRegex(std::string path) {
	std::string start = ".\\Text\\"s;
	std::string end = ".txt"s;

	std::regex base_regex(start + "(.*)" + end);

	std::smatch base_match;
	std::string matched;

	if (std::regex_match(path, base_match, base_regex)) {
		// The first sub_match is the whole string; the next
		// sub_match is the first parenthesized expression.
		if (base_match.size() == 2) {
			matched = base_match[1].str();
		}
	}
	return matched;
}