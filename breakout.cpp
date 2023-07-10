// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

#include "breakout.h"
#include <time.h>
#include "levels.h"

//=============================================================================
// Constructor
//=============================================================================
Breakout::Breakout()
{
    isPaused = false;
    gameOver = false;
    currentScreen = TITLE;
    ballCount = MAX_BALLS;

    Level level1, level2;

    level1.data = {
    STRONG,   // 0
    STRONG,
    STRONG,
    STRONG,
    STRONG,
    STRONG,
    STRONG,
    STRONG,
    STRONG,
    // 9 row 2
    HARD, 
    WEAK,   
    HARD,
    WEAK,
    HARD,
    WEAK,
    HARD,
    WEAK,
    HARD,
    // 18 row 3
    NONE,   
    NONE,
    NONE,   
    NONE,
    NONE,
    NONE,
    NONE,
    NONE,
    NONE,	
    NONE,	// 27
    };

    level2.data = {
    HARD,   // 0
    HARD,
    HARD,
    METAL,
    METAL,
    METAL,
    HARD,
    HARD,
    HARD,
    // 9 row 2
    NONE,   // 0 
    METAL,
    WEAK,
    NONE,
    STRONG,
    NONE,
    WEAK,
    METAL,
    NONE,
    // 18 row 3
    NONE,
    NONE,
    NONE,
    STRONG,
    NONE,
    STRONG,
    NONE,
    NONE,
    NONE,
    NONE,	// 27
    };

    // store levels for easy loading
    levels.push_back(level1);
    levels.push_back(level2);

}

//=============================================================================
// Destructor
//=============================================================================
Breakout::~Breakout()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

/// <summary>
/// Resets score and board
/// </summary>
void Breakout::resetGame()
{
    score = 0;
    currentLevel = 0;
    gameOver = false;
    console.resetLog();
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Breakout::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    initBackgrounds();
    initButtons();

    // Init DirectX font with 48px high Arial
    if (dxScoreFont.initialize(graphics, 48, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score font"));
    
    if (dxBallCount.initialize(graphics, 24, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball count font"));
   
    // init the console log
    console.initialize(graphics);

    // for testing
    if (skipTitleScreen) {
        startNewGame();
    }

    return;
}

/// <summary>
/// Begins a new game from the Title Screen
/// </summary>
void Breakout::startNewGame()
{
    // set proper bg frame
    backgroundImage.setX(- static_cast<int>(GAME_WIDTH));
    currentScreen = GAME;
    gameOver = false;

    initSprites();
    resetGame();
    loadLevel(currentLevel); // level numbers are 0-based... :/

    // play!
    restartBall();
}

//=============================================================================
// Initializes all the game sprites from textures
//=============================================================================
void Breakout::initSprites() {
    // create our game object and graphics
    initShip();
    // set up the blocks
    initBlocks();
    // ball sprite
    initBall();
}


/// <summary>
/// Load background image(s)
/// </summary>
void Breakout::initBackgrounds()
{
    // background texture
    if (!backgroundTexture.initialize(graphics, BG_PATH))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
    }

    // game bg image
    if (!backgroundImage.initialize(graphics, 0, 0, 2, &backgroundTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game bg image"));
    }
}

void Breakout::initButtons()
{
    // background texture
    if (!buttonTexture.initialize(graphics, NG_BUTTON_PATH))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button texture"));
    }

    // game bg image
    if (!newGameButton.initialize(this, 0, 0, 2, &buttonTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button image"));
    }

    newGameButton.setX(400 - newGameButton.getSpriteData().width / 2);
    newGameButton.setY(400);
}

//=============================================================================
// Ship texture and entity init
//=============================================================================
void Breakout::initShip()
{
    if (!shipTexture.initialize(graphics, SHIP_PATH)) {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));
    }
    if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &shipTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship entity"));

    ship.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);

    // start center, near the bottom
    ship.setX(GAME_WIDTH / 2 - shipNS::WIDTH / 2);
    ship.setY(GAME_HEIGHT - 84); 
    ship.setVelocity(VECTOR2(0, 0)); // start standing still
}


//=============================================================================
// Sets the ball at the staring position
//=============================================================================
void Breakout::initBall() 
{
    if (!ballTexture.initialize(graphics, BALL_PATH))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball texture"));
    }
    if (!ball.initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &ballTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball entity"));
    }
}

//=============================================================================
// Create starting blocks
//=============================================================================
void Breakout::initBlocks()
{
    // load our texture, reuse it for all block Entities
    if (!blockTexture.initialize(graphics, BLOCK_PATH))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block texture"));
    }
}

void Breakout::loadLevel(int levelNumber)
{
    const float START_X = 114;
    const float START_Y = 100;
    const int COLS = 9;
    const int ROWS = 3;

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

void Breakout::loadRandomLevel()
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
// Update all game items
//=============================================================================
void Breakout::update()
{
    // check if we want to exit
    CheckForExit();

    // handle inputs on Title Screen only
    if (currentScreen == TITLE) {
        if (newGameButton.isMouseOver()) {
            // over, allow clicks
            if (input->getMouseLButton()) {
                startNewGame();
            }
        }
    }

    // handle Game updates and inputs
    if (currentScreen == GAME) {
        CheckPauseInput();

        if (!isPaused) {
            if (!gameOver) {
                // update position of all game objects
                ship.update(frameTime);
                ball.update(frameTime);

                // blocks
                for (int i = 0; i < blocks.size(); i++) {
                    // only update blocks that need it
                    if (blocks.at(i).getIsAnimating()) {
                        blocks.at(i).update(frameTime);
                    }
                }

                // check if the ball went off below ship
                if (ball.getY() > GAME_HEIGHT - ballNS::HEIGHT) {
                    audio->playCue(ZAP);
                    loseBall();
                    restartBall();
                }
            } // game over
        }  // paused
    } // GAME screen

}

void Breakout::CheckPauseInput()
{
    if (currentScreen == GAME) {
        // SPACE pauses
        if (input->isKeyDown(SPACE_KEY)) {
            isPaused = !isPaused;
        }
    }
}

bool Breakout::isGameOver()
{
    if (ballCount < 1) {
        // game over
        return true;
    }

    return false;
}

void Breakout::loseBall()
{
    ballCount--;
}

//=============================================================================
// Sets the ball at the staring position
//=============================================================================
void Breakout::restartBall()
{
    if (isGameOver()) {
        // show screen
        gameOver = true;
        console.setLogText("GAME OVER!");
    } else {
        ball.setX(220);
        ball.setY(300);
        ball.setVelocity(VECTOR2(ballNS::SPEED, ballNS::SPEED)); // move!
    }
}

//=============================================================================
// allows the ship to wrap around from left to right and vice versa
//=============================================================================
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
    VECTOR2 collisionVector, collisionPosition;

    if (!isPaused) {

        // if collision between ball and ship
        if (ball.collidesWith(ship, collisionVector)) {

            ball.bounceOffShip(collisionVector, collisionPosition, ship.getSpriteData());            
            console.setLogText(ship.toString());

            audio->playCue(CLICK);            
        }

        // collision ball with block
        for (int i = 0; i < blocks.size(); i++) {
            // must use .at() to properly access the actual block object
            // .at() returns a "reference".. hence a pointer is needed to capture it properly
            Block* const block = &blocks.at(i);

            // collidesWith needs an Entity*
            if (ball.collidesWith(blocks.at(i), collisionVector)) {
                ball.bounce(collisionVector, block->getSpriteData());

                // reduce health if possible
                if (block->getBlockType() != INVINCIBLE) {
                    // damage
                    block->damage(BALL);
                    audio->playCue(CLUNK);

                    console.setLogText("Health: " + std::to_string(block->getHealth()));

                    // check if ball is dead
                    if (block->getHealth() <= 0) {
                        // update score
                        score += block->getPointValue();
                        removeBlock(i);
                    }
                } else {
                    // invincible!
                    //block->bounce
                    audio->playCue(CLICK);
                }

            } // end collision if
        } // end loop
    }

}

//=============================================================================
// Remove block that was hit by the ball
//=============================================================================
void Breakout::removeBlock(int index)
{
    audio->playCue(POP);
    blocks.erase(blocks.begin() + index);
}

//=============================================================================
// Render game items
//=============================================================================
void Breakout::render()
{
    try {
        graphics->spriteBegin();
        
        // screen/game state
        switch (currentScreen) {
            case TITLE:
                backgroundImage.draw();
                newGameButton.draw();
                break;
            case GAME:
                renderGameScreen();
                break;
        }
        
        graphics->spriteEnd();
    }
    catch (...) {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::render"));
    }

}

void Breakout::renderGameScreen()
{
    backgroundImage.draw();

    ship.draw();
    ball.draw();

    // render all blocks
    for (int i = 0; i < blocks.size(); i++) {
        blocks.at(i).draw();
    }

    // UI
    renderUI();
    console.renderLog();
}

void Breakout::renderUI() 
{
    // score shadow
    dxScoreFont.setFontColor(graphicsNS::BLACK50);
    dxScoreFont.print("Score: " + std::to_string(score), 9, 9); 

    // score main font
    dxScoreFont.setFontColor(graphicsNS::WHITE);
    dxScoreFont.print("Score: " + std::to_string(score), 7, 7);

    // ball count
    dxBallCount.setFontColor(graphicsNS::FB_HARD);
    dxBallCount.print(std::to_string(ballCount), 7, 40);
}

//=============================================================================
// ESC key quits the game
//=============================================================================
void Breakout::CheckForExit() {
    // ESC key always quits
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
    blockTexture.onLostDevice();
    buttonTexture.onLostDevice();
    dxScoreFont.onLostDevice();
    dxBallCount.onLostDevice();
    console.onLostDevice();
    
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
    ballTexture.onResetDevice();
    blockTexture.onResetDevice();
    buttonTexture.onResetDevice();
    dxScoreFont.onResetDevice();
    dxBallCount.onResetDevice();
    console.onResetDevice();

    Game::resetAll();
    return;
}
