// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 4 spacewar.h v1.0

#ifndef _SPACEWAR_H             // prevent multiple definitions if this 
#define _SPACEWAR_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"

//=============================================================================
// Create game class
//=============================================================================
class Breakout : public Game
{
private:
    // variables
    TextureManager nebulaTexture;
    TextureManager planetTexture;
    TextureManager shipTex;
    Image nebula;
    Image planet;
    Image ship;
    float velocityX;
    float velocityY;

    float radians = 0;
    float thetaDeg = 0;

public:
    // Constructor
    Breakout();

    // Destructor
    virtual ~Breakout();

    // Initialize the game
    void initialize(HWND hwnd);
    void initSprites(); // helper fn
    void update();      // must override pure virtual from Game
    void doCircle();
    void CheckForExit(); // helper to handle exit inputs
    void wrapScreenEdge(); // checks screen bounds
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
    void handleInputAndMomentum();
};

#endif
