#pragma once

#include "constants.h"
#include "block.h"
#include <vector>
#include "level.h"

class LevelManager
{
public:
    std::vector<Level> levels;
    
public:
    
    LevelManager();
    ~LevelManager();


    // level loading
    void loadLevels();  // loads all levels from disk
    // Advances the level
    void loadNextLevel();
    // Loads given level
    void loadLevel(int level);
    // loads a randomly generated level
    void loadRandomLevel();
    // loads the level from a file
    bool loadLevelFromFile(int n);
};

