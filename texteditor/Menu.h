#pragma once
#include <string>
#include "TextHandler.h"

class Menu {

	public:
		std::string MenuControl();
		bool CreateNewTextDocument(std::string name);
		bool SelectDocument(std::string name);
		bool DeleteDocument(std::string name);
		void ListAllOptions(sf::RenderWindow& window, sf::Text text);
};
