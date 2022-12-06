#include  <SFML/Graphics.hpp> // replace quotes with less than and greater than symbols
#include <string>
#include <iostream>
#include "Storage.h"
#include "Display.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Not Tetris");
    sf::Event event;

    Storage storage;
    Display display;

    std::string current_line = "";
    sf::Font font;
    sf::Text text;

    if (!font.loadFromFile("../8bitfont.ttf")) 
    {
        std::cout << "Error loading the font file" << std::endl;
        system("pause");
    }

    while (window.isOpen()) {

        //display.DisplayLineOnScreen("Hello world!", window, sf::Color::White, font, text);

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode != '\b') 
                    {
                        current_line += event.text.unicode;
                        display.DisplayLineOnScreen(current_line, window, sf::Color::White, font, text);
                        window.clear();
                    }

                    if (event.text.unicode == '\b') // User enters backspace
                    {
                        current_line.resize(current_line.size() - 1);
                        display.DisplayLineOnScreen(current_line, window, sf::Color::White, font, text);
                        window.clear();
                    }

                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Enter) 
                { // new line, saving current_line

                }
                if (event.key.code == sf::Keyboard::Backspace) 
                {

                }
            }
        }

    }

    return 0;
}
