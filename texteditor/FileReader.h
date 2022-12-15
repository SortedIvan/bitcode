#pragma once
#include <string>
#include <vector>
#include "Storage.h"

class FileReader {

	public:
		std::vector<std::string> GetAllLinesFromFile(std::string path);
		void FillStorageFromFile(std::string path, Storage& storage);
};