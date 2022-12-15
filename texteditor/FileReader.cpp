#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "FileReader.h"
#include "Storage.h"

std::vector<std::string> FileReader::GetAllLinesFromFile(std::string path) {
    std::vector<std::string> all_content;
    std::ifstream file(path);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            // note that the newline character is not included
            // in the getline() function
            all_content.push_back(line);
            std::cout << line << std::endl;
        }
    }
    return all_content;
}

void FileReader::FillStorageFromFile(std::string path, Storage& storage) {
    std::ifstream file(path);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            // note that the newline character is not included
            // in the getline() function
            storage.AddToLineStorage(line);
            storage.AddToDisplayPool(line + '\n');
        }
    }
}