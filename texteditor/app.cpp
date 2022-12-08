#include  <SFML/Graphics.hpp> // replace quotes with less than and greater than symbols
#include <string>
#include <iostream>

#include "Storage.h"
#include "Display.h"
#include "Utility.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Bitcode");
    sf::Event event;

    Storage storage;
    Display display;
    Utility utility;

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

    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {

                if (event.text.unicode < 128) {
                    if (event.text.unicode != '\b' && event.text.unicode != 13)
                    {
                        current_line += event.text.unicode;
                        // Keeping track of the amount of characters on the current line
                        current_line_character += 1; 

                        window.clear();
                        display.DisplayLineOnScreen(current_line, window, sf::Color::White, font, text, storage.GetDisplayPool());
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
                        window.clear();
                        display.DisplayLineOnScreen(current_line, window, sf::Color::White, font, text, storage.GetDisplayPool());
                       
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
                    window.clear(); // Clear the screen
                    display.DisplayAllLinesFromVector(storage.GetDisplayPool(), window, sf::Color::White, font, text);
                   
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
