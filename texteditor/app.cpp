#include  <SFML/Graphics.hpp> // replace quotes with less than and greater than symbols
#include <string>
#include <iostream>

#include "Storage.h"
#include "Display.h"
#include "Utility.h"
#include "TextHandler.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Bitcode");
    sf::Event event;

    Storage storage;
    Display display;
    Utility utility;
    TextHandler handler;

    bool last_char;
    bool user_typing = false;

    std::string current_line = "";
    int current_line_character = 0;
    sf::Font font;
    sf::Text text;
    

    if (!font.loadFromFile("../8bitfont.ttf")) 
    {
        std::cout << "Error loading the font file" << std::endl;
        system("pause");
    }    
    int line_counter = 0;


    // Testing file handler
    std::vector<std::string>* all_documents = handler.GetAllAvailableDocuments();
    handler.CreateAllDocumentsOnLaunch();
    std::vector<TextDocument>* text_documents = handler.GetTextDocuments();
    std::cout << text_documents->size();
    //
    for (int i = 0; i < text_documents->size(); i++) {
        std::cout << text_documents->at(i).GetDocumentName() << std::endl;
        std::cout << text_documents->at(i).GetDocumentPath() << std::endl;
    }

    //for (int i = 0; i < all_documents->size(); i++) {
    //    std::cout << all_documents->at(i);
    //}
    
    // End of testing file handler



    // Setting the text to be inwards
    text.setOrigin(sf::Vector2f(-70.f, 0.f)); 

    // Creating inwarded text overlay

    // GRAPHICAL INTERFACE -> TO BE EXTRACTED
    sf::Color backgroundColor(0, 32, 63);
    sf::Color textSeperatorColor(173, 239, 209); 

    sf::RectangleShape rect(sf::Vector2f(60.f, 1000.f));
    rect.setPosition(sf::Vector2f(0.f, 0.f));
    rect.setFillColor(textSeperatorColor);
    sf::RenderTexture bgTex;
    bgTex.create(1500, 1000);
    bgTex.draw(rect);
    bgTex.display();

    sf::Sprite background_overlay(bgTex.getTexture());
    
    while (window.isOpen()) {

        window.clear(backgroundColor);
        window.draw(background_overlay);
        display.DrawLineOnScreen(current_line, window, sf::Color::White, font, text, storage.GetDisplayPool());
        window.display();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                user_typing = true;
                if (event.text.unicode < 128) {
                    if (event.text.unicode != '\b' && event.text.unicode != 13)
                    {
                        current_line += event.text.unicode;
                        // Keeping track of the amount of characters on the current line
                        current_line_character += 1; 

                        //window.clear();
                        //display.DisplayLineOnScreen(current_line, window, sf::Color::White, font, text, storage.GetDisplayPool());
                    }

                    if (event.text.unicode == '\b') // User enters backspace
                    {                        
                        last_char = utility.RemoveLastCharFromString(current_line, current_line_character);
                        if (!current_line_character <= 0) {
                            current_line_character -= 1;
                        }

                        if (last_char) 
                        {
                            if (storage.GetLineStorage()->size() != 0) {
                                current_line = storage.GetLineStorage()->back();
                                current_line_character = current_line.size();
                                storage.RemoveLastFromDisplayPool();
                                storage.RemoveLastFromLineStorage();
                            }
                        }
                        //window.clear();
                        //display.DisplayLineOnScreen(current_line, window, sf::Color::White, font, text, storage.GetDisplayPool());
                       
                    }

                }
            }

            if (event.type == sf::Event::KeyReleased) {

                if (event.key.code == sf::Keyboard::Enter) 
                { // new line, saving current_line
                   
                    storage.AddToDisplayPool(current_line + '\n'); // Save line with '\n' for new line
                    storage.AddToLineStorage(current_line);
                    current_line = ""; // Clear out the line
                    current_line_character = 0;
                   
                }
                if (event.key.code == sf::Keyboard::Backspace) 
                {

                }
            }

        }


    }

    return 0;
}

void LineAnimation() 
{

}
