#pragma once
#include <string>
#include <vector>
#include <stack>

class Storage {

	private:
		std::vector<std::string>* display_pool = new std::vector<std::string>();
		std::vector<std::string>* line_storage = new std::vector<std::string>(); 
	public:
		std::vector<std::string>* GetDisplayPool();
		std::vector<std::string>* GetLineStorage();
		void AddToDisplayPool(std::string line);
		void AddToLineStorage(std::string line);
		void RemoveLastFromDisplayPool();
		void RemoveLastFromLineStorage();
		std::string GetLastLineFromDisplayStorage();
		std::string GetLastLineFromLineStorage();
};


