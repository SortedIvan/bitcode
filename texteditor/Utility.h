#pragma once
#include <string>
#include <regex>


class Utility {
	public:
		bool RemoveLastCharFromString(std::string& line, int index);
		std::string MatchStringToRegex(std::regex regexpr, std::string string_to_match);
		std::string MathPathRegex(std::string path);
};