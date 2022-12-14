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
	std::cout << menu_text_options.size() << " is the current size " << std::endl;;

	try {
		for (int i = 0; i < menu_text_options.size(); i++) {
			// EXCEPTION THROWN HERE
			window.draw(menu_text_options.at(i));
		}
	}
	catch (const std::exception& ex) {

		std::cout << "Exception: " << ex.what() << '\n';
	}
}


std::string Menu::MenuControl(TextHandler& handler) {
	Utility utility;
	sf::RenderWindow menu_window(sf::VideoMode(800, 600), "Menu");
	sf::Color backgroundColor(0, 32, 63);
	sf::Event event;
	sf::Font font;
	sf::Text menu_text;
	utility.CheckFontLoaded(font, "../8bitfont.ttf");

	std::vector<sf::Text> menu_text_options = GetAllTextOptions(handler, font);
	int menu_counter = 0; // Start at the first document, count goes up and down with arrows

	menu_text.setOrigin(sf::Vector2f(-20.f, 0.f));
	menu_text.setFont(font);

    while (menu_window.isOpen()) {
        // DRAWING
        menu_window.clear(backgroundColor); // Setting menu background color
        //window.draw(background_overlay);
		
		DrawAllOptions(menu_window, menu_text_options); //ACCESS VIOLATION ERROR

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
					break;
			}

        }
    }
    return "Not correctly working";

}


