#pragma once
#include <string>
#include "Storage.h"

class FileWriter {
	public:
		void WriteOutStorageContentOnFile(Storage& storage, std::string file_path, std::string current_line);
};