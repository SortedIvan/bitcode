#include <string>
#include <fstream> 
#include "Menu.h"
#include "TextHandler.h"



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



