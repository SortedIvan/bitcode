#include "FileWriter.h"
#include "Storage.h"
#include <string>
#include <fstream>

void FileWriter::WriteOutStorageContentOnFile(Storage& storage, std::string file_path, std::string current_line)
{
    std::ofstream text_file(file_path);

    for (int i = 0; i < storage.GetDisplayPool()->size(); i++) 
    {
        text_file << storage.GetDisplayPool()->at(i);
    }
    text_file << current_line;
    text_file.close();
}

