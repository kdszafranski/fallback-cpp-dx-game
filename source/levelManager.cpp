#include "levelManager.h"

void LevelManager::loadLevels() {
    loadLevelFromFile(0);
    loadLevelFromFile(1);
    loadLevelFromFile(2);
    loadLevelFromFile(3);
}

void LevelManager::loadNextLevel()
{
    currentLevel++;
    if (currentLevel >= levels.size()) {
        currentLevel = 0;
    }

    loadLevel(currentLevel);
    restartBall();
}


void LevelManager::loadLevel(int levelNumber)
{
    const float START_X = 114;
    const float START_Y = 100;
    const int COLS = 9;
    const int ROWS = 3;

    blocks.clear();

    // load up vector with blocks from the level data
    int y = START_Y;
    for (int i = 0; i < ROWS; i++) {

        int x = START_X;
        for (int j = 0; j < COLS; j++) {

            if (levels.at(levelNumber).data.at(i * COLS + j) == NONE) {
                // skip
            } else {
                Block newBlock(levels.at(levelNumber).data.at(i * COLS + j));

                if (!newBlock.initialize(this, blockNS::WIDTH, blockNS::HEIGHT, blockNS::TEXTURE_COLS, &blockTexture))
                {
                    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block entity"));
                }

                newBlock.setX(x);
                newBlock.setY(y);
                newBlock.setVelocity(VECTOR2(0, 0));

                // add to vector
                blocks.push_back(newBlock);
            }

            // move to the right
            x += blockNS::WIDTH;
        }

        // set new row downward
        y += blockNS::HEIGHT;
    }

}

void LevelManager::loadRandomLevel()
{
    const float START_X = 82;
    const float START_Y = 100;
    const int COLS = 10;

    srand((unsigned)time(0));
    int y = START_Y;
    for (int i = 0; i < 2; i++) {

        int x = START_X;
        for (int j = 0; j < COLS; j++) {

            // rand() with % is 0-n exclusive 
            BLOCK t = static_cast<BLOCK>((rand() % 5));
            Block newBlock(t);

            if (!newBlock.initialize(this, blockNS::WIDTH, blockNS::HEIGHT, blockNS::TEXTURE_COLS, &blockTexture))
            {
                throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block entity"));
            }

            newBlock.setX(x);
            newBlock.setY(y);
            newBlock.setVelocity(VECTOR2(0, 0));

            // add to vector
            blocks.push_back(newBlock);

            // move to the right
            x += blockNS::WIDTH;
        }

        // set new row downward
        y += blockNS::HEIGHT;
    }

}

//=============================================================================
// Loads a level from disk
//=============================================================================
bool LevelManager::loadLevelFromFile(int n)
{
    string level, str, filename;
    Level loadedLevel;

    level = n + '0';
    filename = "Level" + level;
    filename += ".txt";

    ifstream in(filename); //open existing file

    if (!in) return false; //check if file actual exists return otherwise
    int line = 1;
    while (getline(in, str))
    {
        if (line == 2) {
            loadedLevel.levelName = str;
        }
        if (line > 2) {
            // load the line as a Block
            const char ch = str.at(0);
            // skip comment lines
            if (ch == '/') {
                continue;
            }
            int blockInt = ch - '0'; // this produces the ASCII value of the int we want
            const BLOCK t = static_cast<BLOCK>(blockInt);
            Block newBlock(t);
            loadedLevel.data.push_back(t);
        }

        ++line;

        if (in.eof()) break; //check if end of file is reached
    }

    in.close(); //close file

    levels.push_back(loadedLevel);

    return true;
}