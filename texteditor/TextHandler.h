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
		bool CreateTextDocumentObject(std::string name, std::string path);
		bool GetAllDocumentNames();
		bool CheckIfDocumentAlreadyExists(std::string name);
		std::vector<std::string>* GetAllAvailableDocuments();
		void CreateAllDocumentsOnLaunch();
};