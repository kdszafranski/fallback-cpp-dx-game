// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#ifndef _BREAKOUT_H_             // prevent multiple definitions if this 
#define _BREAKOUT_H_             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "ship.h"
#include "ball.h"
#include "block.h"

//=============================================================================
// Create game class
//=============================================================================
class Breakout : public Game
{
private:
    // variables
    TextureManager backgroundTexture;
    TextureManager ballTexture;
    TextureManager shipTexture;
    TextureManager blockTexture;
    Image backgroundImage;
    Ship ship;
    Ball ball;
    Block block;


public:
    // Constructor
    Breakout();

    // Destructor
    virtual ~Breakout();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

    // Keep things tidy
    void initSprites();
    void initShip();
    void initBall();
    void initBlocks();

    void CheckForExit(); // helper to handle exit inputs

    void doCircle();
    void wrapScreenEdge(); // checks screen bounds
};

#endif
