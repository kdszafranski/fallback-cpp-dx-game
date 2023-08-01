#pragma once

#include "constants.h"
#include <vector>
#include <string>

/// LEVELS

struct Level {
	std::string levelName;
	std::vector<BLOCK> data;
};

