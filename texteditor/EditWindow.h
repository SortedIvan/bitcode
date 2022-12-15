#pragma once
#include  <SFML/Graphics.hpp>
#include "Storage.h"
#include <string>
#include "TextDocument.h"

class EditWindow {
	public:
		int EditorControl(TextDocument& document, Storage& storage);
};