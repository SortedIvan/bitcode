#include  <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream> 
#include "Menu.h"
#include "Display.h"
#include "TextHandler.h"
#include "TextDocument.h"

bool Menu::CreateNewTextDocument(std::string name)
{
	TextHandler handler;

	if (handler.CheckIfDocumentAlreadyExists(name)) {
		return false;
	}

	std::string document_path = R"(.\\Text\\)" + name;
	handler.CreateTextDocumentObject(name, document_path);
	std::ofstream outfile(document_path);
	outfile.close();
	return true;
}

bool Menu::SelectDocument(std::string name) 
{
	TextHandler handler;
	if (handler.CheckIfDocumentAlreadyExists(name)) {
		return true;
	}
	return false;
}

void Menu::ListAllOptions(sf::RenderWindow& window, sf::Text text) {

	TextHandler handler;
	std::vector<TextDocument>* all_available_documents = handler.GetTextDocuments();
	std::string options = "";

	for (int i = 0; i < all_available_documents->size(); i++) {
		options += std::to_string(i) + "| " + all_available_documents->at(i).GetDocumentName();
		options += '\n';
		options += "  - located at: " + all_available_documents->at(i).GetDocumentPath();
		options += '\n';
        options += '\n';
	}
	
	text.setString(options);
	window.draw(text);
}


std::string Menu::MenuControl() {
	TextHandler handler;
	sf::RenderWindow menu_window(sf::VideoMode(800, 600), "Menu");
	sf::Color backgroundColor(0, 32, 63);
	sf::Event event;
	sf::Font font;
	sf::Text menu_text;

	handler.CreateAllDocumentsOnLaunch();
	menu_text.setFont(font);

    while (menu_window.isOpen()) {
        // DRAWING
        menu_window.clear(backgroundColor); // Setting menu background color
        //window.draw(background_overlay);
		ListAllOptions(menu_window, menu_text);
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
    return "";

}


