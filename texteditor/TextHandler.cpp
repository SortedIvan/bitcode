#include <string>
#include <vector>
#include <iostream>
#include <fstream>  
#include <filesystem>
#include <stdio.h>
#include <regex>

#include "TextHandler.h"
#include "TextDocument.h"
#include "Utility.h"

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

bool TextHandler::CreateTextDocumentObject(std::string name, std::string path) 
{
	if (CheckIfDocumentAlreadyExists(name)) {
		return false;
	}
	TextDocument document(name, path);
	text_documents->push_back(document);
	//std::string full_path = R"(.\\Text\\)";
	//full_path += name + ".txt";

	return true;
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


/* Creates TextDocument objects and saves onto vector for easier use (saves path & name of files for easy
	opening and deleting of documents)*/
void TextHandler::CreateAllDocumentsOnLaunch() {
	Utility utility;
	std::vector<std::string>* document_paths = GetAllAvailableDocuments();

	try {
		std::regex regexpr("[^\.\\\\][a-zA-Z0_9]+.txt");
		for (int i = 0; i < document_paths->size(); i++) {
			std::string document_name = utility.MatchStringToRegex(regexpr, document_paths->at(i));
			if (document_name != "") {
				std::cout << document_name << " IS THE NAME AND " << document_paths->at(i) << " IS THE PATH" << std::endl;
				CreateTextDocumentObject(document_name, document_paths->at(i));
			}
		}
	}
	catch (const std::regex_error& ex) {

		std::cout << "Exception: " << ex.what() << '\n';
	}
}