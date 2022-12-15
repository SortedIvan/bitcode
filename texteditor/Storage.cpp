#include "Storage.h"
#include <string>

std::vector<std::string>* Storage::GetDisplayPool() 
{
	return display_pool;
}

std::vector<std::string>* Storage::GetLineStorage() 
{
	return line_storage;
}

void Storage::AddToDisplayPool(std::string line) 
{
	display_pool->push_back(line);
}

void Storage::AddToLineStorage(std::string line) 
{
	line_storage->push_back(line);
}

void Storage::RemoveLastFromDisplayPool() 
{
	if (display_pool->size() > 0) {
		display_pool->pop_back();
	}
}

void Storage::RemoveLastFromLineStorage() 
{
	if (line_storage->size() > 0) 
	{
		line_storage->pop_back();
	}
}

std::string Storage::GetLastLineFromDisplayStorage() 
{
	if (display_pool->size() > 0)
	{
		return display_pool->back();
	}
	return "";
}

std::string Storage::GetLastLineFromLineStorage() 
{
	if (line_storage->size() > 0)
	{
		return line_storage->back();
	}
	return "";
}