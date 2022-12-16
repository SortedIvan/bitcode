#pragma once

#include <string>

class TextDocument {
	private:
		std::string document_name;
		std::string document_path;
	public:
		TextDocument(std::string documentname, std::string documentpath);
		std::string GetDocumentName();
		std::string GetDocumentPath();
		TextDocument() = default;
};