#include  <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Storage.h"
#include "Display.h"
#include "Utility.h"
#include "TextHandler.h"
#include "Menu.h"



// TO DO -> Abstract to utility
void LineCountDraw(int count, sf::Text& line_count_text, sf::RenderWindow& window);
void OnEnterReleased(sf::Event event, Storage& storage, std::string& current_line, int& line_counter, int& current_line_character_count, int& selected_line_char);
void OnUserEntersBackspace(sf::Event event, Storage& storage, Utility& utility, bool& last_char, std::string& current_line, int& current_line_character_count, int& line_counter, int& selected_line_char);
void OnLastCharacterInCurrentLine(Storage& storage, std::string& current_line, int& current_line_character_count, int& line_counter, bool& last_char, int& selected_line_char);
void OnLeftArrowPressed(sf::Event event);
void OnRightArrowPressed(sf::Event event); 
void OnRegularTextEntered(sf::Event event, std::string& current_line, int& current_line_character_count, int& selected_line_char);

int main()
{
    Storage storage;
    Display display;
    Utility utility;
    TextHandler handler;
    Menu menu;

    handler.CreateAllDocumentsOnLaunch();

    if (menu.MenuControl(handler) == "Test") {
        std::cout << "works";
    }

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Bitcode");

    sf::Event event;


    bool last_char;
    bool user_typing = false;

    std::string current_line = "";
    int current_line_character_count = 0;
    int selected_line_char = 0;
    int line_counter = 1; // The amount of lines the text file starts with, has to be abstracted
    sf::Font font;
    sf::Text text;
    sf::Text lineCountText;

    // Loading fonts
    utility.CheckFontLoaded(font, "../8bitfont.ttf");
    // Setting the text to be inwards -> TODO: Make it scalable with screen
    text.setOrigin(sf::Vector2f(-80.f, 0.f));

    // Line counter text, lines shown on left of screen
    lineCountText.setFont(font);
    lineCountText.setFillColor(sf::Color::Black);
    lineCountText.setOrigin(sf::Vector2f(-20.f, 0.f));
     

    // GRAPHICAL INTERFACE -> TO BE EXTRACTED
    sf::Color backgroundColor(0, 32, 63);
    sf::Color textSeperatorColor(173, 239, 209); 

    sf::RectangleShape rect(sf::Vector2f(70.f, 1000.f));
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

            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::TextEntered:
                    user_typing = true;
                    if (event.text.unicode < 128) {
                        //Normal characters entered
                        OnRegularTextEntered(event, current_line, current_line_character_count, selected_line_char);
                        //BACKSPACE
                        OnUserEntersBackspace(event, storage, utility, last_char, current_line, current_line_character_count, line_counter, selected_line_char);
                        // Left and right arrow keys
                        OnLeftArrowPressed(event);
                        OnRightArrowPressed(event);

                    }
                    break;

                case sf::Event::KeyReleased:
                    OnEnterReleased(event, storage, current_line, line_counter, current_line_character_count, selected_line_char);
                    break;

            }

        }
    }
    return EXIT_SUCCESS;
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

void OnEnterReleased(sf::Event event, Storage& storage, std::string& current_line, int& line_counter, int& current_line_character_count, int& selected_line_char) {
    if (event.key.code == sf::Keyboard::Enter)
    { // new line, saving current_line

        storage.AddToDisplayPool(current_line + '\n'); // Save line with '\n' for new line
        storage.AddToLineStorage(current_line);
        current_line = ""; // Clear out the line
        current_line_character_count = 0;


        selected_line_char = 0;
        line_counter += 1;

    }
}

void OnUserEntersBackspace(sf::Event event,Storage& storage, Utility& utility,bool& last_char, std::string& current_line, int& current_line_character_count,int& line_counter, int& selected_line_char) {
    if (event.text.unicode == '\b') // User enters backspace
    {
        // If the character pointer is where the user is, we delete the last character from the current line
        if (current_line_character_count == selected_line_char) {
            last_char = utility.RemoveLastCharFromString(current_line, current_line_character_count);
            if (!current_line_character_count <= 0) {
                current_line_character_count -= 1;
            }
            if (!selected_line_char <= 0) {
                selected_line_char -= 1;
            }
            // If its the last character in the line, we get the next one if there is one
            OnLastCharacterInCurrentLine(storage, current_line, current_line_character_count, line_counter, last_char, selected_line_char);
            return;
        }
        // Otherwise, we remove a character from where the user is currently positioned within the string
        last_char = !utility.RemoveCharFromStr(current_line, selected_line_char);

        if (!current_line_character_count <= 0) {
            current_line_character_count -= 1;
        }
        if (!selected_line_char <= 0) {
            selected_line_char -= 1;
        }
        OnLastCharacterInCurrentLine(storage, current_line, current_line_character_count, line_counter, last_char, selected_line_char);
    }
}

// When the user deletes a character and it is the last one in the string, we get a new line and set the variables accordingly
void OnLastCharacterInCurrentLine(Storage& storage, std::string& current_line, int& current_line_character_count, int& line_counter, bool& last_char, int& selected_line_char) {
    if (last_char)
    {
        if (storage.GetLineStorage()->size() != 0) {
            current_line = storage.GetLineStorage()->back();
            current_line_character_count = current_line.size();
            selected_line_char = current_line.size();
            storage.RemoveLastFromDisplayPool();
            storage.RemoveLastFromLineStorage();

            //TODO: Remove and abstract to actual counter
            if (line_counter - 1 != -1) {
                line_counter -= 1;
            }
        }
    }
}

// When user presses LEFT & RIGHT arrow keys
void OnLeftArrowPressed(sf::Event event) {
    if (event.text.unicode == 37) {

    }
}
void OnRightArrowPressed(sf::Event event) {
    if (event.text.unicode == 38) {

    }
}

// When regular/ a-z text is entered | TODO: Abstracting ctrl+c, shift, etc.
void OnRegularTextEntered(sf::Event event, std::string& current_line, int& current_line_character_count, int& selected_line_char) {
    // If the unicode is not backspace, enter, left or right arrow
    if (event.text.unicode != '\b' && event.text.unicode != 13 && event.text.unicode != '37' && event.text.unicode != '39')
    {
        // if the current selected character is not the size of the line (so the current character is not the last character of the string)
        if (selected_line_char != current_line_character_count) {
            // Add character at the selected index
            current_line[selected_line_char] += event.text.unicode;
            current_line_character_count += 1; // Keeping track of how many characters are in the string
            return;
        }
        // Otherwise, add character at the end of the line
        current_line += event.text.unicode;
        current_line_character_count += 1; // Keeping track of how many characters are in the string
        selected_line_char += 1;
    }
}
