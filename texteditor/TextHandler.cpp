#include <string>
#include <vector>
#include <iostream>
#include <fstream>  
#include <filesystem>
#include <stdio.h>

#include "TextHandler.h"
#include "TextDocument.h"

namespace fs = std::filesystem;

std::vector<TextDocument>* TextHandler::GetTextDocuments()
{
	return text_documents;
}

bool TextHandler::CheckIfDocumentAlreadyExists(std::string name) 
{
	for (int i = 0; i < text_documents->size(); i++) {
		if (GetTextDocuments()->at(i).GetDocumentName() == name) {
			return true;
		}
	}
	return false;
}

bool TextHandler::CreateTextDocument(std::string name, std::string path) 
{
	if (CheckIfDocumentAlreadyExists(name)) {
		return false;
	}
	TextDocument document(name, path);
	text_documents->push_back(document);
	std::string full_path = R"(.\\Text\\)";
	full_path += name + ".txt";

	std::ofstream outfile(full_path);
	outfile.close();
}

TextDocument TextHandler::FindTextDocumentByName(std::string name) {

	try {
		for (int i = 0; i < text_documents->size(); i++) {
			if (text_documents->at(i).GetDocumentName() == name) {
				return text_documents->at(i);
			}
		}
		throw("Not found!");
	}
	catch (std::string exception_details) {
		std::cout << exception_details;
	}
}

std::vector<std::string>* TextHandler::GetAllAvailableDocuments() {
	try {
		std::vector<std::string>* all_documents = new std::vector<std::string>();
		std::string full_path = R"(.\\Text\\)";

		for (const auto& entry : fs::directory_iterator(full_path)) {
			all_documents->push_back(entry.path().u8string());
		}
		return all_documents;
	}
	catch (const std::filesystem::filesystem_error& ex)
	{
		std::cout << "Exception: " << ex.what() << '\n';
	}
}