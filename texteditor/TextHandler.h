#pragma once
#include <string>
#include <vector>
#include "TextDocument.h"

class TextHandler {
	private:
		std::vector<TextDocument>* text_documents = new std::vector<TextDocument>();
	public:
		std::vector<TextDocument>* GetTextDocuments();
		TextDocument FindTextDocumentByName(std::string name);
		bool DeleteTextDocumentByName(std::string name);
		bool CreateTextDocument(std::string name, std::string path);
		bool CheckIfDocumentAlreadyExists(std::string name);
		std::vector<std::string>* GetAllAvailableDocuments();
};