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
#include "Explosion.h"
// Animations
#include "FadeTo.h"
#include "PinchScale.h"
#include "PunchScale.h"
#include "DirectionBounce.h"
#include "MoveTo.h"
#include "ScaleXTo.h"
#include "Shake.h"

//=============================================================================
// Constructor
//=============================================================================
Fallback::Fallback()
{
	editor = new Editor();
	powerUp = NULL;
	racerSpawnTimer = 0;
	hasPowerUp = false;
	powerUpTimer = 0;
	currentPowerUp = FAST; // not actually applied, null would be better
	powerUpTimeLimit = 5.0f;
	animId = 0;
}

//=============================================================================
// Destructor
//=============================================================================
Fallback::~Fallback()
{
	releaseAll();           // call onLostDevice() for every graphics item

	// remove all running animations
	racers.clear();
	m_AnimationManager.abortAllProcesses(true);

	SAFE_DELETE(powerUp);
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
	} else {
		setTitleScreen();
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

	// stop any other animations
	m_AnimationManager.clearAllProcesses();
	explosionManager.clearAllParticles();
	racers.clear();

	// reset game variables
	resetGame();

	// level numbers are 0-based... :/
	loadLevel(currentLevel);

	// play!
	restartBall();
}

/// <summary>
/// Resets score, board, and general game state
/// </summary>
void Fallback::resetGame()
{
	hasPowerUp = false;
	gameOver = false;
	isPaused = false;
	ballCount = MAX_BALLS;
	timer = 0;
	powerUpTimer = 0;
	score = 0;
	currentLevel = 0; // points into levels vector, 0 is the first level
	console.resetLog();
}

void Fallback::exitGame()
{
	console.setLogText("");
	isPaused = true;
	SAFE_DELETE(powerUp);

	// remove animations
	explosionManager.clearAllParticles();
	m_AnimationManager.clearAllProcesses();

	// go to main menu
	setTitleScreen();
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
	// ui/hud
	initUI();

	// power ups texture
	if (!powerUpTexture.initialize(graphics, POWERUP_PATH))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power up texture"));
	}

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
	// title
	if (!titleTexture.initialize(graphics, TITLE_PATH))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing title texture"));
	}

	// game bg image
	if (!titleImage.initialize(graphics, 0, 0, 1, &titleTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing title image"));
	}
	titleImage.setPosition(GAME_WIDTH / 2 - titleImage.getWidth() / 2 + 5, 178);
	//titleImage.setColorFilter(graphicsNS::WHITE & graphicsNS::ALPHA25);
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

	// racers/details
	if (!detailsTexture.initialize(graphics, RACER_PATH)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing details texture"));
	}
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

	//ship.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);
	ship.setCurrentFrame(0);

	// start center, near the bottom
	ship.setX(GAME_WIDTH / 2 - shipNS::WIDTH / 2);
	ship.setY(GAME_HEIGHT - 88);
	ship.setVelocity(VECTOR2(0, 0)); // start standing still

}


//=============================================================================
// Initialize ball texture/images
//=============================================================================
void Fallback::initBall()
{
	if (!iconTexture.initialize(graphics, ICONS_PATH))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball texture"));
	}
	if (!ball.initialize(this, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &iconTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball entity"));
	}
	ball.setCurrentFrame(0);

	// ball shadow image
	if (!shadowBallImage.initialize(graphics, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &iconTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball shadow image"));
	}
	shadowBallImage.setCurrentFrame(4);

}

void Fallback::initUI()
{
	// ball count icon image
	if (!ballCountIcon.initialize(this->graphics, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &iconTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball count icon"));
	}
	ballCountIcon.setCurrentFrame(0);
	ballCountIcon.setPosition(736, 68);

	// ball count X icon
	if (!ballCountXImage.initialize(graphics, ballNS::WIDTH, ballNS::HEIGHT, ballNS::TEXTURE_COLS, &iconTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball count X icon"));
	}
	ballCountXImage.setCurrentFrame(1);
	ballCountXImage.setPosition(ballCountIcon.getX() + ballCountIcon.getWidth() + 4, ballCountIcon.getY());

	// power up stuff
	if (!uiCurrentPowerUpDiamond.initialize(this->graphics, powerupNS::WIDTH, powerupNS::HEIGHT, powerupNS::TEXTURE_COLS, &powerUpTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power up UI icon"));
	}
	uiCurrentPowerUpDiamond.setCurrentFrame(7);
	uiCurrentPowerUpDiamond.setPosition(GAME_WIDTH / 2 - powerupNS::WIDTH, GAME_HEIGHT - powerupNS::HEIGHT * 1.5);

	if (!uiCurrentPowerUpIcon.initialize(this->graphics, powerupNS::WIDTH, powerupNS::HEIGHT, powerupNS::TEXTURE_COLS, &powerUpTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power up Letter"));
	}
	uiCurrentPowerUpIcon.setCurrentFrame(currentPowerUp);
	uiCurrentPowerUpIcon.setPosition(uiCurrentPowerUpDiamond.getPosition());

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
	racers.clear();
	removePowerUp();
	SAFE_DELETE(powerUp);

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
				newBlock.setCurrentFrame(0);
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

		// process animations
		m_AnimationManager.updateProcesses(frameTime);

		if (creditsButton.isMouseOver()) {
			if (input->getMouseLButton()) {
				console.setLogText("launch credits");
			}
		}

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
				if (ballResetting) {
					// move ball with ship
					ball.setPosition((ship.getX() + ship.getWidth() / 2) - ball.getWidth() / 2, ship.getY() - ball.getHeight() - 1);
					// allow input to launch
					if (input->wasKeyPressed(LAUNCH_BALL_KEY)) {
						ball.setVelocity({ 0,-90 });
						ball.removePowerUp(); // resets speed
						ball.activate(); // turn on collisions
						ballResetting = false;
					}
				} else {
					ball.update(frameTime);
				}


				console.setLogText(to_string(ship.getX()));

				timer += frameTime;
				// every second adjust ball trail
				if (timer > BALLSHADOW_INTERVAL) {
					recentBallPositions.push_back(VECTOR2(ball.getX(), ball.getY()));

					if (recentBallPositions.size() > 5) {
						// remove first
						recentBallPositions.erase(recentBallPositions.begin());
					}
					timer = 0;
				}

				// handle power ups
				if (hasPowerUp) {
					powerUpTimer += frameTime;
					if (powerUpTimer > powerUpTimeLimit) {
						removePowerUp();
					}
				}

				// update particles
				explosionManager.update(frameTime);

				// update Entity tweens/animations
				m_AnimationManager.updateProcesses(frameTime);

				// update falling power up
				if (powerUp) {
					powerUp->update(frameTime);
					// off the screen?
					if (powerUp->getY() > GAME_HEIGHT) {
						SAFE_DELETE(powerUp);
					}
				}

				// check if the ball went off below ship
				if (ball.getY() > GAME_HEIGHT) {
					audio->playCue(ZAP);
					loseBall();
					restartBall();
				}

				// every 5 seconds there is a chance to spawn racers
				racerSpawnTimer += frameTime;
				if (racerSpawnTimer > 5) {
					spawnRacers();
					racerSpawnTimer = 0;
				}

			} // game over

		}  // paused
	} // GAME screen

	if (currentScreen == EDITOR) {
		editor->update(frameTime);
		// process animations
		m_AnimationManager.updateProcesses(frameTime);
	}

	// they run on all screens
	cleanUpRacerList();

}

#pragma region Racers
void Fallback::spawnRacers()
{
	// chance
	srand((unsigned)time(0));
	int numberToSpawn = 0;

	numberToSpawn = rand() % 4;
	Vector2 position = { GAME_WIDTH, rand() % GAME_HEIGHT };
	for (int i = 0; i < numberToSpawn; i++) {
		spawnRacerAnimation(position);
		position.x += 25;
		position.y += 3;
	}

}

void Fallback::spawnRacerAnimation(Vector2 startPos)
{
	Image racersImage;
	racersImage.myId = ++animId;

	if (!racersImage.initialize(graphics, 32, 2, 0, &detailsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing racers image"));

	racersImage.setPosition(startPos);
	Vector2 end = startPos;
	end.x -= GAME_WIDTH + racersImage.getWidth(); // go  832 pixels from start

	racers.push_back(racersImage);

	//  = rand() % 100 + 1;     // v2 in the range 1 to 100
	StrongAnimationPtr racerMove = std::make_shared<MoveTo>(&racers.back(), rand() % 4 + 2, end);
	m_AnimationManager.attachProcess(racerMove);
}

void Fallback::cleanUpRacerList()
{
	std::list<Image>::iterator it = racers.begin();
	while (it != racers.end()) {
		if (it->canDestroy()) {
			racers.erase(it++);
		}
		if (it != racers.end()) {
			it++;
		}
	}
}
#pragma endregion


#pragma region PowerUps

// Creates the Entity on the screen
void Fallback::spawnPowerUp(VECTOR2 position)
{
	// spawn powerup
	if (powerUp == NULL) {
		const int n = rand() % 7;
		powerUp = new PowerUp(static_cast<POWERUP>(n), position);
		powerUp->initialize(this, 32, 32, 8, &powerUpTexture);
	}
}

// applies the collided Power up
void Fallback::applyPowerUp()
{
	hasPowerUp = true;
	powerUpTimer = 0;
	currentPowerUp = powerUp->getPowerUpType();

	if (currentPowerUp == MYSTERY) {
		int pick = rand() % 6; // pick one of the others
		currentPowerUp = static_cast<POWERUP>(pick);
	}

	// apply to the correct Entity and spawn animations
	StrongAnimationPtr anim;
	switch (currentPowerUp) {
		case SLOW:
		case ZOOM:
			ball.applyPowerUp(currentPowerUp);
			break;
		case FAST:
			ship.applyPowerUp(currentPowerUp);
			break;
		case GROW:
			anim = std::make_shared<ScaleXTo>(&ship, 0.5f, 1.5f);
			m_AnimationManager.attachProcess(anim);
			break;
		case TINY:
			anim = std::make_shared<ScaleXTo>(&ship, 0.5f, 0.5f);
			m_AnimationManager.attachProcess(anim);
			break;
	}

	// update HUD icons
	uiCurrentPowerUpIcon.setCurrentFrame(currentPowerUp);
	currentPowerUpColor = powerUp->getColor();

	// bounce the UI power up icon
	StrongAnimationPtr bounce = std::make_shared<PunchScale>(&uiCurrentPowerUpDiamond, 0.2f, 1.5f);
	m_AnimationManager.attachProcess(bounce);
}

void Fallback::removePowerUp()
{
	if (hasPowerUp) {
		// allow end of power up animations
		switch (currentPowerUp) {
			case FAST:
				ship.resetSpeed();
			case GROW:
			case TINY:
				StrongAnimationPtr reset = std::make_shared<ScaleXTo>(&ship, 0.5, 1.0f);
				m_AnimationManager.attachProcess(reset);
				break;

		}
	}

	hasPowerUp = false;
	powerUpTimer = 0;

	// clear up speeds and such
	ball.removePowerUp();
}
#pragma endregion

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

//=============================================================================
// Reset things so a new ball works like the beginning of the game
//=============================================================================
void Fallback::loseBall()
{
	//ballCount--;

	// we lose power ups
	if (hasPowerUp) {
		removePowerUp();
	}

	// shake ship
	Vector2 shakeLimits = { 10.0f, 10.0f };
	StrongAnimationPtr shipShake = std::make_shared<Shake>(&ship, 0.5, shakeLimits);
	m_AnimationManager.attachProcess(shipShake);
	StrongAnimationPtr bgShake = std::make_shared<Shake>(&backgroundImage, 0.5, shakeLimits);
	m_AnimationManager.attachProcess(bgShake);

	

	// bounce ball UI icon
	StrongAnimationPtr animPtr = std::make_shared<PunchScale>(&ballCountIcon, 0.2f, 1.5f);
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
		ballResetting = true;
		ball.setActive(false);
		ball.setPosition((ship.getX() + ship.getWidth() / 2) - ball.getWidth() / 2, ship.getY() - ball.getHeight() - 1);
		ball.setVelocity(VECTOR2(0, 0));

		recentBallPositions.clear();
		//recentBallPositions.push_back(VECTOR2(ball.getX(), ball.getY()));
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

		// active power up collides with ship
		if (powerUp) {
			// powerUp is a ptr so dereference with *powerUp
			if (ship.collidesWith(*powerUp, collisionVector)) {
				audio->playCue(ZAP);

				score += POWERUP_POINT_VALUE;
				applyPowerUp();

				explosionManager.spawnExplosion(this, &iconTexture, { powerUp->getX(), powerUp->getY() });

				// remove power up entity
				SAFE_DELETE(powerUp);
			}
		}

		// collision ball with block
		for (int i = 0; i < blocks.size(); i++) {
			// must use .at() to properly access the actual block object
			// .at() returns a "reference".. hence a pointer is needed to capture it properly
			Block* const block = &blocks.at(i);
			int direction = 0;

			// collidesWith needs an Entity*
			if (ball.collidesWith(blocks.at(i), collisionVector)) {
				ball.bounce(collisionVector, block->getSpriteData(), direction);

				// reduce health if possible
				if (block->getBlockType() != INVINCIBLE) {
					audio->playCue(CLUNK);

					// check if ball is dead
					block->damage(BALL);
					if (block->getHealth() <= 0) {
						score += block->getPointValue() * 2; // double for destroying the block
						removeBlock(i);
					} else {
						score += block->getPointValue();
						// fire off animation process
						StrongAnimationPtr pinch = std::make_shared<PinchScale>(&blocks.at(i), 0.10f, 0.80f);
						m_AnimationManager.attachProcess(pinch);
					}
				} else {
					// invincible!
					// bounce away from ball
					Vector2 end = block->getPosition();
					switch (direction) {
						case 1:
							// go down
							end.y += 3.0f;
							break;
						case 2: // go left
							end.x -= 3.0f;
							break;
						case 3: // go up
							end.y -= 3.0f;
							break;
						case 4: // go right
							end.x += 3.0f;
							break;
						default: // 0 up
							end.y -= 3.0f;
					}
					// reset just in case
					block->setCurrentFrame(0);

					StrongAnimationPtr bounce = std::make_shared<DirectionBounce>(&blocks.at(i), 0.15f, end);
					m_AnimationManager.attachProcess(bounce);
					// set filled, animation will reset when complete
					block->setCurrentFrame(1);

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
	// explode
	const VECTOR2 pos = {
		blocks.at(index).getCenterX(),
		blocks.at(index).getCenterY()
	};

	// send parts flying
	explosionManager.spawnExplosion(this, &iconTexture, pos);

	// destroying blocks increases the ball speed
	ball.bumpSpeedUp();

	// no power up entity in play and ship has no powerup
	if (powerUp == NULL && !hasPowerUp) {
		spawnPowerUp(pos);
	}

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
				renderTitleScreen();
				break;
			case GAME:
				renderGameScreen();
				break;
			case EDITOR:
				backgroundImage.draw();
				renderRacers();
				editor->draw();
				break;
		}

		graphics->spriteEnd();
	}
	catch (...) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::render"));
	}

}

void Fallback::renderTitleScreen()
{
	backgroundImage.draw();
	// racers behind UI
	renderRacers();

	titleImage.draw();
	newGameButton.draw();
	editorButton.draw();
	creditsButton.draw();
	console.renderLog();
}

/// <summary>
/// Loops thru and renders any background vfx
/// </summary>
void Fallback::renderRacers()
{
	int i = 0;
	for (auto& racer : racers) {
		if (i % 2 == 0) {
			racer.draw(graphicsNS::ALPHA75);
		} else {
			racer.draw();
		}
		++i;
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
	racers.clear();
	m_AnimationManager.clearAllProcesses();

	// set bg 
	backgroundImage.setX(0);

	spawnRacers();

	isPaused = false;
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

	renderRacers();

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
			shadowBallImage.draw(graphicsNS::WHITE & graphicsNS::ALPHA50, true); // ??
		}

		ball.draw();
	}


	// render all blocks
	for (int i = 0; i < blocks.size(); i++) {
		blocks.at(i).draw();
	}

	// particles
	explosionManager.draw();

	// power up
	if (powerUp) {
		powerUp->draw();
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
	ballCountIcon.draw(ballCountIcon.getColorFilter(), true);
	ballCountXImage.draw();

	// power ups
	if (hasPowerUp) {
		uiCurrentPowerUpDiamond.draw(currentPowerUpColor, true);
		uiCurrentPowerUpIcon.draw();
	}
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
				PostQuitMessage(0); // quits app
				break;
			case GAME:
				exitGame();
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
	titleTexture.onLostDevice();
	iconTexture.onLostDevice();
	shipTexture.onLostDevice();
	blockTexture.onLostDevice();
	buttonTexture.onLostDevice();
	gameOverTexture.onLostDevice();
	detailsTexture.onLostDevice();

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
	titleTexture.onResetDevice();
	iconTexture.onResetDevice();
	shipTexture.onResetDevice();
	detailsTexture.onResetDevice();
	blockTexture.onResetDevice();
	buttonTexture.onResetDevice();
	gameOverTexture.onResetDevice();

	dxScoreFont.onResetDevice();
	dxBallCount.onResetDevice();
	console.onResetDevice();

	Game::resetAll();
	return;
}
