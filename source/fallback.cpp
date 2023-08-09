// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly

using namespace std;
#include "fallback.h"
#include <time.h>
#include "level.h"
#include <fstream>
#include <iostream>
#include "editor.h"
#include "fileHandler.h"
// Animations
#include "FadeTo.h"
#include "PinchScale.h"
#include "PunchScale.h"

//=============================================================================
// Constructor
//=============================================================================
Fallback::Fallback()
{
	editor = new Editor();
	resetGame();
	setTitleScreen();
}

//=============================================================================
// Destructor
//=============================================================================
Fallback::~Fallback()
{
	releaseAll();           // call onLostDevice() for every graphics item

	// remove all running animations
	m_AnimationManager.abortAllProcesses(true);

	SAFE_DELETE(editor);
}


//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Fallback::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	initBackgrounds();
	initButtons();

	// Init DirectX font 
	if (dxScoreFont.initialize(graphics, 62, true, false, "Agdasima") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score font"));

	if (dxBallCount.initialize(graphics, 34, true, false, "Agdasima") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball count font"));

	// init the console log
	console.initialize(graphics);

	// load all levels from files on disk
	loadLevelFiles();

	// for testing
	if (skipTitleScreen) {
		startNewGame();
	}

	return;
}


/// <summary>
/// Begins a new game from the Title Screen
/// </summary>
void Fallback::startNewGame()
{
	// set proper bg screen state
	setGameScreen();

	// load game sprites
	initSprites();

	// reset game variables
	resetGame();

	// level numbers are 0-based... :/
	loadLevel(currentLevel);

	// play!
	restartBall();
}

/// <summary>
/// Resets score and board
/// </summary>
void Fallback::resetGame()
{
	timer = 0;
	ballCount = MAX_BALLS;
	gameOver = false;
	isPaused = false;
	score = 590;
	currentLevel = 0; // points into levels vector, 0 is the first level
	console.resetLog();
}

//=============================================================================
// Initializes all the game sprites from textures
//=============================================================================
void Fallback::initSprites() {
	// misc graphics
	initMessageSprites();
	// create our game object and graphics
	initShip();
	// set up the blocks
	initBlocks();
	// ball sprites
	initBall();
}


/// <summary>
/// Load background image(s)
/// </summary>
void Fallback::initBackgrounds()
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

void Fallback::initButtons()
{
	// buttons texture
	if (!buttonTexture.initialize(graphics, NG_BUTTON_PATH))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button texture"));
	}

	// create buttons from above spritesheet/texture
	if (!newGameButton.initialize(this, 256, 64, 3, &buttonTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button image"));
	}
	newGameButton.setCurrentFrame(0);
	newGameButton.setPosition(400 - newGameButton.getSpriteData().width / 2, 356);

	if (!editorButton.initialize(this, 256, 64, 3, &buttonTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button image"));
	}
	editorButton.setCurrentFrame(2);
	editorButton.setPosition(400 - editorButton.getSpriteData().width / 2, 432);

	// credits
	if (!creditsButton.initialize(this, 256, 64, 3, &buttonTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button image"));
	}

	creditsButton.setCurrentFrame(1);
	creditsButton.setPosition(400 - creditsButton.getSpriteData().width / 2, 510);
}

void Fallback::initMessageSprites()
{
	// background texture
	if (!gameOverTexture.initialize(graphics, GAME_OVER_PATH))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing message texture"));
	}

	// game bg image
	if (!gameOverImage.initialize(graphics, 0, 0, 0, &gameOverTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game over image"));
	}
	gameOverImage.setPosition(0, GAME_HEIGHT / 2);



}

//=============================================================================
// Ship texture and entity init
//=============================================================================
void Fallback::initShip()
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
// Initialize ball texture/images
//=============================================================================
void Fallback::initBall()
{
	if (!ballTexture.initialize(graphics, ICONS_PATH))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball texture"));
	}
	if (!ball.initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &ballTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball entity"));
	}
	ball.setCurrentFrame(0);

	// ball shadow image
	if (!shadowBallImage.initialize(graphics, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &ballTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball shadow image"));
	}
	shadowBallImage.setCurrentFrame(0);
	
	// ball count icon image
	if (!ballCountIcon.initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &ballTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball count icon"));
	}
	ballCountIcon.setActive(false); // no collisions please
	ballCountIcon.setCurrentFrame(0);
	ballCountIcon.setPosition(736, 68);
	
	// ball count X icon
	if (!ballCountXImage.initialize(graphics, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &ballTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball count X icon"));
	}
	ballCountXImage.setCurrentFrame(1);
	ballCountXImage.setPosition(ballCountIcon.getX() + ballCountIcon.getWidth() + 4, ballCountIcon.getY());
}

//=============================================================================
// Initialize block texture/images
//=============================================================================
void Fallback::initBlocks()
{
	// load our texture, reuse it for all block Entities
	if (!blockTexture.initialize(graphics, BLOCK_PATH))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block texture"));
	}
}

void Fallback::loadLevelFiles() {
	levels.clear();
	loadLevelFromFile(0); // Editor default
	loadLevelFromFile(1);
	loadLevelFromFile(2);
	loadLevelFromFile(3);
}

void Fallback::startNextLevel()
{
	currentLevel++;
	if (currentLevel >= levels.size()) {
		currentLevel = 0;
	}

	m_AnimationManager.clearAllProcesses();

	loadLevel(currentLevel);
	restartBall();
}

/// <summary>
/// Creates the blocks in the vector from the list given level data which was previously loaded
/// </summary>
/// <param name="levelNumber">number that matches level number</param>
void Fallback::loadLevel(int levelNumber)
{
	const int START_X = 114;
	const int START_Y = 100;
	const int COLS = 9;
	const int ROWS = 3;

	blocks.clear();
	blocks.reserve(21); // 27 is max space needed

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

				newBlock.setPosition(x, y);
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

/// <summary>
/// Generates a level of random blocks
/// </summary>
void Fallback::loadRandomLevel()
{
	constexpr int START_X = 82;
	constexpr int START_Y = 100;
	constexpr int COLS = 10;

	blocks.clear();
	blocks.reserve(21);

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

			newBlock.setPosition(x, y);
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
bool Fallback::loadLevelFromFile(int n)
{
	Level loadedLevel;
	FileHandler loader;

	if (loader.loadLevelFromFile(loadedLevel, n)) {
		// editor level
		if (n == 0) {
			// replacing
			if (levels.size() > 0) {
				levels.at(0) = loadedLevel;
				return true;
			}
		}

		levels.push_back(loadedLevel);
	} else {
		return false;
	}

	return true;
}

//=============================================================================
// Update all game items
//=============================================================================
void Fallback::update(float frameTime)
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
		if (editorButton.isMouseOver()) {
			if (input->getMouseLButton()) {
				launchEditor();
			}
		}

		m_AnimationManager.updateProcesses(frameTime);

		/*if (creditsButton.isMouseOver()) {
			if (input->getMouseLButton()) {
				console.setLogText("launch credits");
			}
		}*/

		// too lazy for the mouse
		if (input->wasKeyPressed(ENTER_KEY)) {
			startNewGame();
		}
	}

	// handle Game updates and inputs
	if (currentScreen == GAME) {
		CheckPauseInput();
		CheckCheatInput();

		if (!isPaused) {
			if (!gameOver) {
				// update position of all game objects
				ship.update(frameTime);

				timer += frameTime;

				// every second
				if (timer > BALLSHADOW_INTERVAL) {
					recentBallPositions.push_back(VECTOR2(ball.getX(), ball.getY()));

					if (recentBallPositions.size() > 5) {
						// remove first
						recentBallPositions.erase(recentBallPositions.begin());
					}

					timer = 0;
				}

				ball.update(frameTime);
				
				// run animations
				m_AnimationManager.updateProcesses(frameTime);

				// check if the ball went off below ship
				if (ball.getY() > GAME_HEIGHT - ballNS::HEIGHT) {
					audio->playCue(ZAP);
					loseBall();
					restartBall();
				}
			} // game over
		}  // paused
	} // GAME screen

	if (currentScreen == EDITOR) {
		editor->update(frameTime);
	}

}

void Fallback::CheckPauseInput()
{
	if (currentScreen == GAME) {
		// SPACE pauses
		if (input->wasKeyPressed(SPACE_KEY)) {
			isPaused = !isPaused;
		}
	}
}

void Fallback::CheckCheatInput()
{
	if (currentScreen == GAME) {
		// next level
		if (input->wasKeyPressed(NEXT_LEVEL_KEY)) {
			startNextLevel();
		}
	}
}

bool Fallback::isGameOver()
{
	if (ballCount < 1) {
		// game over
		return true;
	}

	return false;
}

void Fallback::loseBall()
{
	ballCount--;

	// bounce icon
	StrongAnimationPtr animPtr = std::make_shared<PunchScale>(&ballCountIcon, 1.6f, 1);
	m_AnimationManager.attachProcess(animPtr);
}

//=============================================================================
// Sets the ball at the staring position
//=============================================================================
void Fallback::restartBall()
{
	if (isGameOver()) {
		// show screen
		gameOver = true;
		console.setLogText("GAME OVER!");
	} else {
		ball.setPosition(220, 300);
		ball.setVelocity(VECTOR2(ballNS::SPEED, ballNS::SPEED)); // move!

		recentBallPositions.clear();
		recentBallPositions.push_back(VECTOR2(ball.getX(), ball.getY()));
	}
}

//=============================================================================
// allows the ship to wrap around from left to right and vice versa
//=============================================================================
void Fallback::wrapScreenEdge() {
	// left/right bounds wrapping
	if (ship.getX() > GAME_WIDTH) {
		// off the edge to the right
		ship.setX((float)-ship.getWidth());
	} else if (ship.getX() < -ship.getWidth()) {
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
void Fallback::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Fallback::collisions()
{
	VECTOR2 collisionVector, collisionPosition;

	if (!isPaused) {

		// if collision between ball and ship
		if (ball.collidesWith(ship, collisionVector)) {
			ball.bounceOffShip(collisionVector, collisionPosition, ship.getSpriteData());
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
					// soundfx
					audio->playCue(CLUNK);
					
					// check if ball is dead
					if (block->getHealth() <= 0) {
						// update score
						score += block->getPointValue();
						removeBlock(i);
					} else {
						// fire off animation process
						StrongAnimationPtr animBounce = std::make_shared<PinchScale>(&blocks.at(i), 0.2f, 0.85f);
						m_AnimationManager.attachProcess(animBounce);
					}
				} else {
					// invincible!
					audio->playCue(CLICK);
				}

			} // end collision if
		} // end blocks loop

		// see if we got'em all
		checkGameOver();
	}

}

//=============================================================================
// Remove block that was hit by the ball
//=============================================================================
void Fallback::removeBlock(int index)
{
	audio->playCue(POP);
	blocks.erase(blocks.begin() + index);
}

void Fallback::checkGameOver()
{
	bool isFinished = false;
	int invincibleCount = 0;
	if (blocks.size() <= 0) {
		isFinished = true;
	} else {
		for (int i = 0; i < blocks.size(); i++) {
			// check each block, as soon as there is a normal block we can stop
			if (blocks.at(i).getBlockType() == INVINCIBLE) {
				invincibleCount++;
			} else {
				return;
			}
		}

	}

	// we're done here, next please!
	if (isFinished || blocks.size() == invincibleCount) {
		startNextLevel();
	}
}

//=============================================================================
// Render game items
//=============================================================================
void Fallback::render()
{
	try {
		graphics->spriteBegin();

		// screen/game state
		switch (currentScreen) {
		case TITLE:
			backgroundImage.draw();
			newGameButton.draw();
			editorButton.draw();
			creditsButton.draw();
			textButton.draw();
			console.renderLog();
			break;
		case GAME:
			renderGameScreen();
			break;
		case EDITOR:
			backgroundImage.draw();
			editor->draw();
			break;
		}

		graphics->spriteEnd();
	}
	catch (...) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::render"));
	}

}

/// <summary>
/// Preps the move to the gameplay screen
/// </summary>
void Fallback::setGameScreen()
{
	// shift to next sprite frame for the game bg
	backgroundImage.setX(-static_cast<int>(GAME_WIDTH));
	currentScreen = GAME;
}

void Fallback::setEditorScreen()
{
	backgroundImage.setX(-static_cast<int>(GAME_WIDTH));
	currentScreen = EDITOR;
}

/// <summary>
/// Preps to move to the Title Screen
/// </summary>
void Fallback::setTitleScreen()
{
	// clean up game
	blocks.clear();
	m_AnimationManager.clearAllProcesses();

	// set bg 
	backgroundImage.setX(0);

	StrongAnimationPtr animBounce = std::make_shared<PinchScale>(&creditsButton, 2.0f, 0.25f);

	//StrongAnimationPtr animBounce = std::make_shared<FadeTo>(&creditsButton, 1.0f, 0.5f);
	m_AnimationManager.attachProcess(animBounce);

	currentScreen = TITLE;
}

void Fallback::launchEditor()
{
	if (!blockTexture.getTexture()) {
		initBlocks();
	}

	// share our stuff
	if (editor->initialized == false) {
		if (editor->initialize(this, &buttonTexture, &blockTexture, &console)) {
			// TODO handle error
		}
	}

	if (editor->initialized) {
		// let's go!
		editor->start();
		setEditorScreen();
	}

}

void Fallback::renderGameScreen()
{
	backgroundImage.draw();

	if (gameOver) {
		// show message
		gameOverImage.draw();
	} else {
		ship.draw();

		for (int i = recentBallPositions.size() - 1; i > -1; i--) {
			shadowBallImage.setPosition(
				recentBallPositions.at(i).x,
				recentBallPositions.at(i).y
			);
			if (i > 0) { // leaves the last 2 the same size
				shadowBallImage.setScale(i * 0.23);
			}
			shadowBallImage.draw(graphicsNS::BLACK50); // ??
		}

		ball.draw();
	}


	// render all blocks
	for (int i = 0; i < blocks.size(); i++) {
		blocks.at(i).draw();
	}

	// UI
	renderUI();
	console.renderLog();
}

void Fallback::renderUI()
{
	RECT scoreRect;
	scoreRect.left = 654;	// upper left X
	scoreRect.top = 10;		// upper left Y
	scoreRect.right = GAME_WIDTH - 8; // lower right X
	scoreRect.bottom = scoreRect.top + 48;	// lower right Y

	// score shadow
	dxScoreFont.setFontColor(graphicsNS::GRAY & graphicsNS::ALPHA50);
	dxScoreFont.print(std::to_string(score), scoreRect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);

	// score main font, adjust rect position up and left
	scoreRect.left = 649;	// upper left X
	scoreRect.top = 7;		// upper left Y
	scoreRect.right = GAME_WIDTH - 11;
	scoreRect.bottom = scoreRect.top + 48;
	dxScoreFont.setFontColor(graphicsNS::WHITE);
	dxScoreFont.print(std::to_string(score), scoreRect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);

	// ball count number
	scoreRect.left = GAME_WIDTH - 24;	// upper left X
	scoreRect.top += 51;				// upper left Y
	scoreRect.right = GAME_WIDTH;		// lower right X
	scoreRect.bottom = scoreRect.top + 32;	// lower right Y
	dxBallCount.setFontColor(getBallCountColor());
	dxBallCount.print(std::to_string(ballCount), scoreRect, DT_LEFT | DT_SINGLELINE);

	// ball count icon and x
	ballCountIcon.draw(ballCountIcon.getColorFilter());
	ballCountXImage.draw();
}

COLOR_ARGB Fallback::getBallCountColor()
{
	switch (ballCount) {
	case 1:
		return graphicsNS::FB_HARD;
		break;
	case 2:
		return graphicsNS::FB_STRONG;
		break;
	case 3:
		return graphicsNS::FB_INVINCIBLE;
		break;
	}

	return graphicsNS::WHITE;
}

//=============================================================================
// ESC key quits the game
//=============================================================================
void Fallback::CheckForExit() {
	// ESC key always quits
	if (input->wasKeyPressed(ESC_KEY)) {
		switch (currentScreen) {
		case TITLE:
			PostQuitMessage(0);
			break;
		case GAME:
			setTitleScreen();
			break;
		case EDITOR:
			exitEditor();
			break;
		}
	}
}

void Fallback::exitEditor()
{
	// clean up
	//SAFE_DELETE(editor);
	console.setLogText("");
	loadLevelFiles();
	setTitleScreen();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Fallback::releaseAll()
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
void Fallback::resetAll()
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
