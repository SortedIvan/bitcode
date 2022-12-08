#pragma once

#include <string>

class TextDocument {
	private:
		std::string document_name;
		std::string document_path;
	public:
		TextDocument(std::string document_name, std::string document_path);
		std::string GetDocumentName();
		std::string GetDocumentPath();
};