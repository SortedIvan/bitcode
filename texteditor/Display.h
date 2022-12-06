#pragma once
#include  <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Display {

	public:
		void DisplayLineOnScreen(std::string line, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text text, std::vector<std::string>* vectorPointer);
		void DisplayAllLinesFromVector(std::vector<std::string>* vectorPointer, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text text);
		void DisplayCharOnScreen(char character, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text text);
};
