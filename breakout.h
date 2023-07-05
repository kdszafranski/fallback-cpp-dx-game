// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#ifndef _BREAKOUT_H_             // prevent multiple definitions if this 
#define _BREAKOUT_H_             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include <stdlib.h>
#include <vector>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "ship.h"
#include "ball.h"
#include "block.h"
#include "textDX.h"

//=============================================================================
// Create game class
//=============================================================================
class Breakout : public Game
{
private:
    // variables
    std::vector<Block> blocks;
    std::string logText;
    int score;

    // Game objects
    TextDX *dxFont;
    TextDX *dxLogFont;

    TextureManager backgroundTexture;
    TextureManager ballTexture;
    TextureManager shipTexture;
    TextureManager blockTexture;
    Image backgroundImage;
    Ship ship;
    Ball ball;
    Block block;

    // pausing
    bool isPaused;


public:
    // Constructor
    Breakout();

    // Destructor
    virtual ~Breakout();

    // Initialize the game
    void initialize(HWND hwnd);
    void ResetGame();

    // Game Loop stuff
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void renderScore();
    void renderLog();
    void releaseAll();
    void resetAll();
    
    // gameplay methods
    void removeBlock(int index);
    void restartBall();

    // Keep things tidy
    void initSprites();
    void initShip();
    void initBall();
    void initBlocks();

    void setLog(std::string message);

    void CheckForExit(); // helper to handle exit inputs

    void wrapScreenEdge(); // checks screen bounds
};

#endif
