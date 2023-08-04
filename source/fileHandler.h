#pragma once
#include "constants.h"
#include "level.h"
#include "blockbutton.h"
#include <string>
#include <vector>

class FileHandler
{

public:
	FileHandler();
	~FileHandler();

	bool loadLevelFromFile(Level& lRef, int levelNumber);
	bool saveLevelToDisk(std::vector<BlockButton> &blocks, int cols, int levelNumber);
};

