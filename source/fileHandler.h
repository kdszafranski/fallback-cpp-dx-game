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

	/// <summary>Loads given level number from disk</summary>
	/// <param name="lRef">Reference to Level from caller</param>
	/// <param name="levelNumber">number of level which coincides with filename</param>
	/// <returns>true on successful loading, false otherwise</returns>
	bool loadLevelFromFile(Level& lRef, int levelNumber);

	/// <summary>Writes out blocks vector to file, line by line, to match Level file format </summary>
	/// <param name="blocks">vector of block data</param>
	/// <param name="cols">number of columns</param>
	/// <param name = "levelNumber">number of level which coincides with filename< / param>
	/// <returns>true on successful loading, false otherwise</returns>
	bool saveLevelToDisk(std::vector<BlockButton> &blocks, int cols, int levelNumber);
};

