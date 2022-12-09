#include <string>
#include "TextDocument.h"

TextDocument::TextDocument(std::string documentname, std::string documentpath) {
	document_name = documentname;
	document_path = documentpath;
}

std::string TextDocument::GetDocumentName() {
	return document_name;
}

std::string TextDocument::GetDocumentPath() {
	return document_path;
}