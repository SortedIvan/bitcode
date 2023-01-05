#pragma once
#include <string>
#include "TextHandler.h"
#include "Storage.h"

class Menu {

	public:
		int MenuControl(TextHandler& handler);
		bool MenuCreationControl(TextHandler& handler);
		bool CreateNewTextDocument(std::string name, TextHandler& handler);
		bool SelectDocument(std::string name, TextHandler& handler);
		bool DeleteDocument(std::string name);
		void DrawAllOptions(sf::RenderWindow& window, std::vector<sf::Text>& menu_text_options);
		std::vector<sf::Text> GetAllTextOptions(TextHandler& handler, sf::Font& font);
};
