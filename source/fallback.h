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
#include "button.h"
#include "textButton.h"
#include "console.h"
#include "editor.h"
#include "AnimationManager.h"
#include "level.h"
#include <memory>

//=============================================================================
// Create game class
//=============================================================================
class Fallback : public Game
{
private:
    // variables
    // testing
    bool skipTitleScreen = false;

    std::vector<Block> blocks;
    std::vector<Level> levels;
    bool gameOver = false;
    int score;
    int ballCount;
    int currentLevel;

    // Game objects
    TextDX dxScoreFont;
    TextDX dxBallCount;
    Console console;
    Editor* editor;
    AnimationManager m_AnimationManager;

    // textures/sprites
    TextureManager backgroundTexture;
    TextureManager ballTexture;
    TextureManager shipTexture;
    TextureManager blockTexture;
    TextureManager buttonTexture;
    TextureManager gameOverTexture;
    Image backgroundImage;
    Image gameOverImage;
    Entity ballCountIcon; // just the ship sprite
    Image ballCountXImage;
    Button newGameButton;
    Button editorButton;
    Button creditsButton;
    TextButton textButton;


    // ball shadow
    float timer;
    Image shadowBallImage;
    std::vector<VECTOR2> recentBallPositions;

    // sprites
    Ship ship;
    Ball ball;
    Block block;

    // pausing
    bool isPaused;


public:
    // Constructor
    Fallback();

    // Destructor
    virtual ~Fallback();

    // Initialize the game
    void initialize(HWND hwnd);
    void resetGame();

    // Game Loop stuff
    void update(float frameTime);      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();  // render game objects
    void renderGameScreen();
    void renderUI(); // display UI
    void releaseAll();
    void resetAll();
    void loseBall();    // reduce ball count
    bool isGameOver();  // check if we're out of balls
    
    // gameplay methods
    void removeBlock(int index);
    void restartBall();
    COLOR_ARGB getBallCountColor();

    // Game state/flow
    void startNewGame();
    void initBackgrounds();
    void initButtons();
    void initSprites();
    void initShip();
    void initBall();
    void initBlocks();
    void initMessageSprites();
    void setTitleScreen();
    void setGameScreen();
    void setEditorScreen();
    // checks if there are blocks left
    void checkGameOver();

    // Editor
    void launchEditor();
    void exitEditor();

    // level loading
    void loadLevelFiles();  // loads all levels from disk
    // Advances the level
    void startNextLevel();
    // Loads given level
    void loadLevel(int level);
    // loads a randomly generated level
    void loadRandomLevel();
    // loads the level from a file
    bool loadLevelFromFile(int n);


    // helper to handle exit inputs
    void CheckForExit(); 
    // helper to handle pause input
    void CheckPauseInput(); 
    // helper to handle cheat inputs
    void CheckCheatInput();

    // checks screen bounds
    void wrapScreenEdge(); 
};

#endif
