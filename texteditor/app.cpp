#include  <SFML/Graphics.hpp> // replace quotes with less than and greater than symbols
#include <string>
#include <iostream>

#include "Storage.h"
#include "Display.h"
#include "Utility.h"
#include "TextHandler.h"


// TO DO -> Abstract to utility
void LineCountDraw(int count, sf::Text& line_count_text, sf::RenderWindow& window);

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
    int line_counter = 1; // The amount of lines the text file starts with, has to be abstracted
    sf::Font font;
    sf::Text text;
    sf::Text lineCountText;


    if (!font.loadFromFile("../8bitfont.ttf")) 
    {
        std::cout << "Error loading the font file" << std::endl;
        system("pause");
    }    
   
    // Setting the text to be inwards -> TODO: Make it scalable with screen
    text.setOrigin(sf::Vector2f(-70.f, 0.f));

    // Line counter text, lines shown on left of screen
    lineCountText.setFont(font);
    lineCountText.setFillColor(sf::Color::Black);
    lineCountText.setOrigin(sf::Vector2f(-30.f, 0.f));
     

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

        // DRAWING
        window.clear(backgroundColor);
        window.draw(background_overlay);
        LineCountDraw(line_counter, lineCountText, window);
        display.DrawLineOnScreen(current_line, window, sf::Color::White, font, text, storage.GetDisplayPool());

        // DISPLAYING
        window.display();


        // TO DO - ABSTRACT USER INPUT LOGIC
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


                                //TODO: Remove and abstract to actual counter
                                if (line_counter - 1 != -1) {
                                    line_counter -= 1;
                                }
                            }
                        }
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
                    line_counter += 1;
                   
                }
                if (event.key.code == sf::Keyboard::Backspace) 
                {

                }
            }

        }


    }

    return 0;
}

void LineCountDraw(int count, sf::Text& line_count_text, sf::RenderWindow& window) {
    std::string lines = "";
    for (int i = 0; i < count; i++) {
        lines += std::to_string(i);
        lines += '\n';
    }

    line_count_text.setString(lines);
    window.draw(line_count_text);
}
