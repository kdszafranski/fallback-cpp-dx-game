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
#include "Button.h"
#include "console.h"
#include "levels.h"

//=============================================================================
// Create game class
//=============================================================================
class Breakout : public Game
{
private:
    // variables
    // testing
    bool skipTitleScreen = true;

    std::vector<Block> blocks;
    int score;
    Level level1;

    // Game objects
    TextDX dxScoreFont;
    Console console;

    // textures/sprites
    TextureManager backgroundTexture;
    TextureManager ballTexture;
    TextureManager shipTexture;
    TextureManager blockTexture;
    TextureManager buttonTexture;
    Image backgroundImage;
    Button newGameButton;

    // sprites
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
    void resetGame();

    // Game Loop stuff
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void renderScore();
    void releaseAll();
    void resetAll();
    
    // gameplay methods
    void removeBlock(int index);
    void restartBall();

    // Game state/flow
    void startNewGame();
    void initBackgrounds();
    void initButtons();
    void initSprites();
    void initShip();
    void initBall();
    void initBlocks();

    // levels
    void loadLevel(int level);
    void loadRandomLevel();

    // user input handlers
    void CheckForExit(); // helper to handle exit inputs
    void CheckPauseInput(); // helper to handle pause input

    void wrapScreenEdge(); // checks screen bounds
};

#endif
