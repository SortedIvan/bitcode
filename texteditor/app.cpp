#include  <SFML/Graphics.hpp> // replace quotes with less than and greater than symbols
#include <string>
#include <iostream>
#include "Storage.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Not Tetris");
    sf::Event event;
    Storage storage;

    std::string current_line = "";
    sf::Font font;
    if (!font.loadFromFile("../bitcodetbe/8bitfont.ttf")) 
    {
        std::cout << "Error loading the font file" << std::endl;
        system("pause");
    }

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode != '\b') 
                    {

                    }
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Enter) 
                {

                }
                if (event.key.code == sf::Keyboard::Backspace) 
                {

                }
            }
        }

    }

    return 0;
}
