// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine Part 1
// Chapter 4 spacewar.cpp v1.0
// Spacewar is the class we create.

#include "breakout.h"

//=============================================================================
// Constructor
//=============================================================================
Breakout::Breakout()
{
    velocityX = 0;
    velocityY = 0;
}

//=============================================================================
// Destructor
//=============================================================================
Breakout::~Breakout()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Breakout::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    initSprites();

    return;
}

//=============================================================================
// Initializes all the game sprites from textures
//=============================================================================
void Breakout::initSprites() {
    // nebula texture
    if (!backgroundTexture.initialize(graphics, BG_PATH))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));
    }
    // nebula
    if (!backgroundImage.initialize(graphics, 0, 0, 0, &backgroundTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula image"));
    }

    // ship texture
    if (!shipTex.initialize(graphics, SHIP_PATH))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));
    }
    // ship has multiple frames, start with upper-left frame
    if (!ship.initialize(graphics, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTex))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship image"));
    }
    // start above and left of planet
    ship.setX(GAME_WIDTH / 4);
    ship.setY(GAME_HEIGHT / 4);
    // animate
    ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
    ship.setCurrentFrame(SHIP_START_FRAME);
    ship.setFrameDelay(SHIP_ANIM_DELAY);
    //ship.setDegrees(45.0f);

}

//=============================================================================
// Update all game items
//=============================================================================
void Breakout::update()
{
    // check if we want to exit
    CheckForExit();

    // update position of all game objects
    ship.update(frameTime);
 
    // handle input controls
    handleInputAndMomentum();   

    // check edge bounds
    wrapScreenEdge();
}

//=============================================================================
// Handle input, flipping the sprite and velocity/momentum
//=============================================================================
void Breakout::handleInputAndMomentum() {
    // move right
    if (input->isKeyDown(SHIP_RIGHT_KEY)) {
        ship.flipHorizontal(false);
        velocityX += frameTime * SHIP_SPEED;        
    }
    // move left
    if (input->isKeyDown(SHIP_LEFT_KEY)) {
        ship.flipHorizontal(true);
        velocityX -= frameTime * SHIP_SPEED;
    }
    // move up
    if (input->isKeyDown(SHIP_DOWN_KEY)) {
        velocityY += frameTime * SHIP_SPEED;
    }
    // move down
    if (input->isKeyDown(SHIP_UP_KEY)) {
        velocityY -= frameTime * SHIP_SPEED;
    }

    // keep our velocity within limits
    if (velocityX > MAX_VELOCITY)
        velocityX = MAX_VELOCITY; // hold on there, ranger
    
    if (velocityX < -MAX_VELOCITY)
        velocityX = -MAX_VELOCITY;
    // limit Y velocity
    if (velocityY > MAX_VELOCITY)
        velocityY = MAX_VELOCITY;
    
    if (velocityY < -MAX_VELOCITY)
        velocityY = -MAX_VELOCITY;

    // keep moving
    ship.setX(ship.getX() + frameTime * velocityX);
    ship.setY(ship.getY() + frameTime * velocityY);
}

void Breakout::wrapScreenEdge() {
    // left/right bounds wrapping
    if (ship.getX() > GAME_WIDTH) {
        // off the edge to the right
        ship.setX((float)-ship.getWidth());
    } else if(ship.getX() < -ship.getWidth()) {
        ship.setX((float)GAME_WIDTH); // top left of image
    }

    // top/bottom bounds wrapping
    if (ship.getY() > GAME_HEIGHT) {
        // off the bottom edge, place it at the top
        ship.setY((float)-ship.getHeight());
    } else if (ship.getY() < -ship.getHeight()) {
        // off the top edge, place it at the bottom
        ship.setY((float)GAME_HEIGHT);
    }
}



//=============================================================================
// Artificial Intelligence
//=============================================================================
void Breakout::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Breakout::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Breakout::render()
{
    try {
        graphics->spriteBegin();
        backgroundImage.draw();
        ship.draw();
        graphics->spriteEnd();
    }
    catch (...) {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::render"));
    }

}


void Breakout::CheckForExit() {
    // ESC key
    if (input->isKeyDown(ESC_KEY)) {
        PostQuitMessage(0);
    }

    // typed exit? or pressed B button
    if (input->getTextIn() == "exit" || input->getGamepadB(0)) {
        PostQuitMessage(0);
    }
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Breakout::releaseAll()
{
    backgroundTexture.onLostDevice();
    planetTexture.onLostDevice();
    shipTex.onLostDevice();
    
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Breakout::resetAll()
{
    backgroundTexture.onResetDevice();
    planetTexture.onResetDevice();
    shipTex.onResetDevice();

    Game::resetAll();
    return;
}
