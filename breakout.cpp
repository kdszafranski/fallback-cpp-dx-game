// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#include "breakout.h"

//=============================================================================
// Constructor
//=============================================================================
Breakout::Breakout()
{
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
    // background texture
    if (!backgroundTexture.initialize(graphics, BG_PATH))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
    }
    // background
    if (!backgroundImage.initialize(graphics, 0, 0, 0, &backgroundTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula image"));
    }

    // ship texture and entity init
    if (!shipTexture.initialize(graphics, SHIP_PATH)) {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));
    }
    if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &shipTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship entity"));

    ship.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);

    // start center, near the bottom
    ship.setX(GAME_WIDTH / 2 - shipNS::WIDTH / 2);
    ship.setY(GAME_HEIGHT - 82);
    ship.setVelocity(VECTOR2(0, 0)); // start standing still


    // ball texture and entity init
    if (!ballTexture.initialize(graphics, BALL_PATH))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball texture"));
    }
    if (!ball.initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &ballTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball entity"));
    }

    ball.setVelocity(VECTOR2(ballNS::SPEED, ballNS::SPEED)); // move!

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
    ball.update(frameTime);
 
    // check edge bounds
    //wrapScreenEdge();
}

//=============================================================================
// Handle input, flipping the sprite and velocity/momentum
//=============================================================================
void Breakout::handleInputAndMomentum() {
    // move right
    if (input->isKeyDown(SHIP_RIGHT_KEY)) {
        ship.setX(ship.getX() + frameTime * shipNS::SPEED);
        //velocityX += frameTime * shipNS::SPEED;
    }
        
    // move left
    if (input->isKeyDown(SHIP_LEFT_KEY)) {
        ship.setX(ship.getX() - frameTime * shipNS::SPEED);
        //velocityX -= frameTime * shipNS::SPEED;
    }

    // keep our velocity within limits
    //if (velocityX > MAX_VELOCITY)
    //    velocityX = MAX_VELOCITY; // hold on there, ranger
    //
    //if (velocityX < -MAX_VELOCITY)
    //    velocityX = -MAX_VELOCITY;

    // keep moving
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
{
    VECTOR2 collisionVector;
    // if collision between ship and planet
    if (ball.collidesWith(ship, collisionVector))
    {
        // bounce off planet
        //ball.bounce(collisionVector, ship);
        ball.setVelocity(VECTOR2(ball.getVelocity().x, -ball.getVelocity().y));
        //ship1.damage(PLANET);
    }

}

//=============================================================================
// Render game items
//=============================================================================
void Breakout::render()
{
    try {
        graphics->spriteBegin();

        backgroundImage.draw();
        ship.draw();
        ball.draw();
        
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
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Breakout::releaseAll()
{
    backgroundTexture.onLostDevice();
    ballTexture.onLostDevice();
    shipTexture.onLostDevice();
    
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
    shipTexture.onResetDevice();

    Game::resetAll();
    return;
}
