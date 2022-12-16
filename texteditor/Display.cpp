#include "Display.h"
#include  <SFML/Graphics.hpp>
#include <string>
#include <vector>

void Display::DisplayAllLinesFromVector(std::vector<std::string>* vectorPointer, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text text)
{
	text.setFont(font);
	text.setFillColor(color);
	std::string all_text = "";


	for (int i = 0; i < vectorPointer->size(); i++) {
		all_text += vectorPointer->at(i);
	}

	text.setString(all_text);
	window.draw(text);
	window.display();
}

void Display::DrawLineOnScreen(std::string line, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text& text, std::vector<std::string>* vectorPointer)
{

	std::string all_text = "";
	for (int i = 0; i < vectorPointer->size(); i++) {
		all_text += vectorPointer->at(i);
	}

	text.setFont(font);
	text.setFillColor(color);
	text.setString(all_text + line);

	window.draw(text);
	//window.display(); // TESTING WITHOUT DISPLAY
}

void Display::DisplayCharOnScreen(char character, sf::RenderWindow& window, sf::Color color, sf::Font font, sf::Text text)
{
	text.setFont(font);
	text.setFillColor(color);
	text.setString(character);

	window.draw(text);
	window.display();
}

void Display::DisplayStringOnScreen(std::string text_str, sf::RenderWindow & window, sf::Color color, sf::Font font, sf::Text text)
{
	text.setFont(font);
	text.setFillColor(color);
	text.setString(text_str);

	window.draw(text);
	window.display();
}