#pragma once
#include <string>
#include "TextHandler.h"

class Menu {

	public:
		std::string MenuControl(TextHandler& handler);
		bool CreateNewTextDocument(std::string name, TextHandler& handler);
		bool SelectDocument(std::string name, TextHandler& handler);
		bool DeleteDocument(std::string name);
		void ListAllOptions(sf::RenderWindow& window, sf::Text text, TextHandler& handler);
};
