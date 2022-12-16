#include  <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Storage.h"
#include "Display.h"
#include "Utility.h"
#include "TextHandler.h"
#include "Menu.h"
#include "FileReader.h"
#include "EditWindow.h"

int main()
{
    Storage storage;
    Display display;
    Utility utility;
    TextHandler handler;
    Menu menu;
    FileReader reader;
    EditWindow editor_window;

    handler.CreateAllDocumentsOnLaunch();// Find all documents at specified path and create object instances
    // Make user choose document and save it as reference
    TextDocument documentChoice = handler.GetTextDocuments()->at(menu.MenuControl(handler));
     
    // Fill out the storage with the according document
    reader.FillStorageFromFile(documentChoice.GetDocumentPath(), storage);

    // Start window
    editor_window.EditorControl(documentChoice, storage);

    return EXIT_SUCCESS;
}
