#include "Display.h"
#include  <SFML/Graphics.hpp>
#include <string>
#include <vector>

void Display::DisplayAllLinesFromVector(std::vector<std::string>* vectorPointer, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text text)
{
	text.setFont(font);
	text.setFillColor(color);

	for (int i = 0; i < vectorPointer->size(); i++) {
		text.setString(vectorPointer->at(i));
		window.draw(text);
		window.display();
	}
}

void Display::DisplayLineOnScreen(std::string line, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text text)
{
	text.setFont(font);
	text.setFillColor(color);
	text.setString(line);

	window.draw(text);
	window.display();
}

void Display::DisplayCharOnScreen(char character, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text text)
{
	text.setFont(font);
	text.setFillColor(color);
	text.setString(character);

	window.draw(text);
	window.display();

}