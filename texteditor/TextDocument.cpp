#include <string>
#include "TextDocument.h"

TextDocument::TextDocument(std::string document_name, std::string document_path) {
	document_name = document_name;
	document_path = document_path;
}

std::string TextDocument::GetDocumentName() {
	return document_name;
}