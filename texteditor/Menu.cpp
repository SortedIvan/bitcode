#include  <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Utility.h"
#include "Menu.h"
#include "Display.h"
#include "TextHandler.h"
#include "TextDocument.h"

#include <thread>
using namespace std::chrono_literals;


void OnArrowsUpAndDownPress(sf::Event event, int& menu_counter, int menu_options_amount);
void HighlightSelectedOption(std::vector<sf::Text>& text_options, sf::Color highlight_color, int selected);

bool Menu::CreateNewTextDocument(std::string name, TextHandler& handler)
{
	if (handler.CheckIfDocumentAlreadyExists(name)) {
		return false;
	}

	std::string document_path = R"(.\\Text\\)" + name;
	handler.CreateTextDocumentObject(name, document_path);
	std::ofstream outfile(document_path);
	outfile.close();
	return true;
}

bool Menu::SelectDocument(std::string name, TextHandler& handler) 
{
	if (handler.CheckIfDocumentAlreadyExists(name)) {
		return true;
	}
	return false;
}

std::vector<sf::Text> Menu::GetAllTextOptions(TextHandler& handler, sf::Font& font) {
	std::vector<TextDocument>* all_available_documents = handler.GetTextDocuments();
	std::vector<sf::Text> menu_text_options;

	for (int i = 0; i < all_available_documents->size(); i++) {
		sf::Text text;
		text.setFont(font);
		text.setString(std::to_string(i) + ") " + all_available_documents->at(i).GetDocumentName());
		menu_text_options.push_back(text);
	}
	return menu_text_options;
	
}

// ACCESS VIOLATION ERROR
void Menu::DrawAllOptions(sf::RenderWindow& window, std::vector<sf::Text>& menu_text_options) {

	//std::cout << menu_text_options.size() << " is the current size " << std::endl;
	try {
		for (int i = 0; i < menu_text_options.size(); i++) {
			// EXCEPTION THROWN HERE
			// Making sure that the text is seperated
			menu_text_options.at(i).setPosition(sf::Vector2f(10.f, 35.f * i));
			window.draw(menu_text_options.at(i));
		}
	}
	catch (const std::exception& ex) {

		std::cout << "Exception: " << ex.what() << '\n';
	}
}


std::string Menu::MenuControl(TextHandler& handler) {
	//sf::Text::findCharacterPos() IMPORTANT!
	Utility utility;
	sf::RenderWindow menu_window(sf::VideoMode(800, 600), "Menu");
	sf::Color backgroundColor(0, 32, 63);
	sf::Color highlight_text_color(173, 239, 209);
	sf::Event event;
	sf::Font font;
	sf::Text menu_text;
	utility.CheckFontLoaded(font, "../8bitfont.ttf");

	std::vector<sf::Text> menu_text_options = GetAllTextOptions(handler, font);
	int menu_counter = 0; // Start at the first document, count goes up and down with arrows
	int menu_options_amount = menu_text_options.size();


	menu_text.setOrigin(sf::Vector2f(-20.f, 0.f));
	menu_text.setFont(font);

    while (menu_window.isOpen()) {
        // DRAWING
        menu_window.clear(backgroundColor); // Setting menu background color

		HighlightSelectedOption(menu_text_options, sf::Color::Black, menu_counter);

		DrawAllOptions(menu_window, menu_text_options);

        // DISPLAYING
        menu_window.display();

        // TO DO - ABSTRACT USER INPUT LOGIC
        while (menu_window.pollEvent(event)) {

            switch (event.type)
            {
				case sf::Event::Closed:
					menu_window.close();
					return "Test";
					break;

				case sf::Event::TextEntered:
					if (event.text.unicode < 128) {

					}
					break;

				case sf::Event::KeyReleased:
					OnArrowsUpAndDownPress(event, menu_counter, menu_options_amount);
					break;
			}

        }
    }
    return "Not correctly working";

}


void OnArrowsUpAndDownPress(sf::Event event, int& menu_counter, int menu_options_amount) 
{
	if (event.key.code == sf::Keyboard::Up)
	{
		if (menu_counter - 1 >= 0) 
		{
			menu_counter -= 1;
			std::cout << menu_counter;
		}
	}
	if (event.key.code == sf::Keyboard::Down)
	{
		if (menu_counter + 1 <= (menu_options_amount - 1)) 
		{
			menu_counter += 1;
			std::cout << menu_counter;
		}
	}
}

void HighlightSelectedOption(std::vector<sf::Text>& text_options, sf::Color highlight_color, int selected) 
{
	for (int i = 0; i < text_options.size(); i++) {
		if (i != selected) {
			text_options.at(i).setFillColor(sf::Color::White);
			continue;
		}
		text_options.at(i).setFillColor(highlight_color);
	}
}