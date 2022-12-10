#pragma once
#include <string>
#include "TextHandler.h"

class Menu {

	public:
		bool CreateNewTextDocument(std::string name);
		bool SelectDocument(std::string name);
		bool DeleteDocument(std::string name);
		void ListAllOptions();
};
