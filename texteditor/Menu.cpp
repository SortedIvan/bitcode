#include  <SFML/Graphics.hpp>
#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Utility.h"
#include "Menu.h"
#include "Display.h"
#include "TextHandler.h"
#include "TextDocument.h"

using namespace std::chrono_literals;
void OnArrowsUpAndDownPress(sf::Event event, int& menu_counter, int menu_options_amount);
void HighlightSelectedOption(std::vector<sf::Text>& text_options, sf::Color highlight_color, int selected);


// Create text document objects, saving their paths and names. Furthermore, create an actual text document using ofstream
bool Menu::CreateNewTextDocument(std::string name, TextHandler& handler)
{
	if (handler.CheckIfDocumentAlreadyExists(name)) {
		return false;
	}

	std::string document_path = R"(.\\Text\\)" + name;
	handler.CreateTextDocumentObject(name, document_path);
	std::ofstream outfile(document_path);

	outfile << std::endl;
	outfile.flush();
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

// Return all of the text documents currently available for editing
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

// Render all of the text documents on the screen
void Menu::DrawAllOptions(sf::RenderWindow& window, std::vector<sf::Text>& menu_text_options) {

	//! Previously encountered -> access violation error
	try {
		for (int i = 0; i < menu_text_options.size(); i++) {
			//! Previously encountered - exception thrown
			
			// Making sure that the text is seperated
			menu_text_options.at(i).setPosition(sf::Vector2f(10.f, 35.f * i));
			window.draw(menu_text_options.at(i));
		}
	}
	catch (const std::exception& ex) {

		std::cout << "Exception: " << ex.what() << '\n';
	}
}

// Main function for controlling and rendering the menu. 
// The function returns an integer which represents the chosen by the user document.
int Menu::MenuControl(TextHandler& handler) {
	//sf::Text::findCharacterPos() -- Potentially necessary function
	Utility utility;
	sf::RenderWindow menu_window;
	menu_window.create(sf::VideoMode(800, 600), "Menu");

	sf::Color backgroundColor(0, 32, 63);
	sf::Color highlight_text_color(173, 239, 209);
	sf::Event event;
	sf::Font font;
	sf::Text menu_text;
	sf::Text new_doc_text;
	

	new_doc_text.setFont(font);
	new_doc_text.setString("Create new file: Press N");
	new_doc_text.setPosition(30, 550);

	utility.CheckFontLoaded(font, "../8bitfont.ttf");

	std::vector<sf::Text> menu_text_options = GetAllTextOptions(handler, font);
	std::vector<TextDocument>* all_available_documents = handler.GetTextDocuments();
	int menu_counter = 0; // Start at the first document, count goes up and down with arrows
	int menu_options_amount = menu_text_options.size();


	menu_text.setOrigin(sf::Vector2f(-20.f, 0.f));
	menu_text.setFont(font);


    while (menu_window.isOpen()) {
        // -------------------- DRAWING -----------------------------------

        menu_window.clear(backgroundColor); // Setting menu background color
		HighlightSelectedOption(menu_text_options, sf::Color::Black, menu_counter);
		DrawAllOptions(menu_window, menu_text_options);
		menu_window.draw(new_doc_text);

        // ------------------ DISPLAYING -----------------------------------
        menu_window.display();

        // TODO: User input logic to be abstracted
        while (menu_window.pollEvent(event)) {

            switch (event.type)
            {
				case sf::Event::Closed:
					menu_window.close();
					return 1;
					break;

				case sf::Event::TextEntered:
					if (event.text.unicode < 128) {

					}

					break;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Enter)
					{
						menu_window.close();
						return menu_counter;
					}

					if (event.key.code == sf::Keyboard::N) {
						menu_window.close();
						MenuCreationControl(handler);
					}
					
					// Controlling the user input with ^ v arrows
					OnArrowsUpAndDownPress(event, menu_counter, menu_options_amount);
					break;
			}

        }
    }
    return -1;

}

bool Menu::MenuCreationControl(TextHandler& handler)
{
	Utility utility;
	sf::RenderWindow menu_creation_window(sf::VideoMode(700, 400), "Create new text file");
	sf::Text document_creation_text;
	sf::Text document_menu_text;
	sf::Font font;

	std::string full_path_new_text = R"(.\\Text\\)";

	utility.CheckFontLoaded(font, "../8bitfont.ttf");

	document_menu_text.setString("Enter a name for your document: ");
	document_menu_text.setPosition(20, 150);
	document_menu_text.setFillColor(sf::Color::White);
	document_menu_text.setFont(font);

	document_creation_text.setPosition(50, 185);
	document_creation_text.setFillColor(sf::Color::White);
	document_creation_text.setFont(font);

	sf::Color backgroundColor(0, 32, 63);
	std::string new_document_name;

	sf::Event event;


	while (menu_creation_window.isOpen()) {
		// -------------------- DRAWING -----------------------------------

		menu_creation_window.clear(backgroundColor); // Setting menu background color
		menu_creation_window.draw(document_menu_text);
		menu_creation_window.draw(document_creation_text);

		// ------------------ DISPLAYING -----------------------------------

		menu_creation_window.display();

		// TODO: User input logic to be abstracted
		while (menu_creation_window.pollEvent(event)) {

			switch (event.type)
			{
			case sf::Event::Closed:
				menu_creation_window.close();
				return 1;
				break;

			case sf::Event::TextEntered:
				if (event.text.unicode == '\b') {
					utility.RemoveCharFromStr(new_document_name, new_document_name.size());
					document_creation_text.setString(new_document_name);
				}
				if (event.text.unicode < 128) {
					// Potentially dangerous: 128 unicode characters contain characters that cannot be used in text names
					if (event.text.unicode != '\b') {
						new_document_name += event.text.unicode;
						document_creation_text.setString(new_document_name);
					}
				}
				
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Enter)
				{
					menu_creation_window.close();
				
					// Text document to be created here
					if (CreateNewTextDocument(new_document_name, handler)) {
						MenuControl(handler);
						return true;
					}
					else {
						document_creation_text.setFillColor(sf::Color::Yellow);
					}
				}

				break;
			}

		}
	}
	return false;
}

// Simple counter to sipher through the text options using the arrow keys
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

// Change the fill color of the text object that is currently selected
// TODO: Graphical change
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


