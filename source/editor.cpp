#include "editor.h"
#include "fileHandler.h"
#include <fstream>
#include <iostream>
using namespace std;

Editor::Editor()
{
	dirty = false;
	currentType = WEAK;
	currentLevel = 0;
	initialized = false;
}

Editor::~Editor()
{
	// I feel like there should be stuff to do here
	// delete in reverse order??
	textButtonList.clear();
}

bool Editor::initialize(Game* pGame, TextureManager* textButtonTexM, TextureManager* blockTexM, Console* pCons)
{
	constexpr int buttonSpacing = 106;
	constexpr int buttonY = 400;
	input = pGame->getInput();
	game = pGame;
	blockTexture = blockTexM;

	// UI BUTTONS
	int startX = 160;
	for (int i = 0; i < 5; i++) {
		BlockButton newButton;
		if (!newButton.initialize(game, 64, 64, 0, blockTexM))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
			return false;
		}
		newButton.setPosition(startX, buttonY);
		newButton.changeBlockType(static_cast<BLOCK>(i));
		startX += buttonSpacing;

		brushSelectorButtonList.push_back(newButton);
	}

	// set the current button
	setCurrentButtonBrush(&brushSelectorButtonList.at(0));

	// Save Button
	if (!saveButton.initialize(game, 200, 64, 0, textButtonTexM))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text button image"));
		return false;
	}
	saveButton.setText("SAVE LEVEL " + to_string(currentLevel));
	saveButton.setPosition(GAME_WIDTH / 2 - saveButton.getSpriteData().width / 2, 500);
	// set the font draw rect inside the button
	saveButton.calculateDrawRect();


	// Build level loading buttons
	// https://cplusplus.com/forum/beginner/70653/
	const int levelButStart = 100;
	for (int i = 0; i < 4; i++) {
		// create a really new allocation each time, remem to delete in Deconstructor
		shared_ptr<TextButton> tb = std::make_shared<TextButton>();
		if (!(*tb).initialize(game, 150, 64, 0, textButtonTexM)) {
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text button image"));
			return false;
		}
		tb->setText("Level " + std::to_string(i));
		tb->setFontSize(18);
		tb->setIntValue(i);
		tb->setPosition(levelButStart + 150 * i, 12);
		tb->calculateDrawRect();

		textButtonList.push_back(std::move(tb));
	}

	// set up console
	console = pCons;
	console->setLogText("EDITOR MODE");

	initialized = true;

	return true;
}

/// <summary>
/// Loads up level 0 and starts editor UI
/// </summary>
void Editor::start()
{
	dirty = false;
	currentType = WEAK;
	currentLevel = 0;
		
	loadCurrentEditorLevel();
}

void Editor::setCurrentButtonBrush(BlockButton* btn) {
	// set new current brush
	currentType = btn->getBlockType();
	btn->setSelected(true);

	// reset all other buttons
	for (int i = 0; i < brushSelectorButtonList.size(); i++) {
		// does this work?
		if (btn != &brushSelectorButtonList.at(i)) {
			brushSelectorButtonList.at(i).setSelected(false);
		}
	}
}

void Editor::update(float frameTime)
{
	// LEVEL LOADING buttons
	// since the vector is just pointers, can use auto on the iterator (it)
	for (auto it : textButtonList) {
		if (it->isMouseOver()) {
			if (input->getMouseLButton()) {
				console->setLogText("loading file " + std::to_string(it->getIntValue()));
				currentLevel = it->getIntValue();
				loadCurrentEditorLevel();
				saveButton.setText("SAVE LEVEL " + to_string(currentLevel));
			}
		}
	}

	// SAVE BUTTON
	if (saveButton.isMouseOver()) {
		if (input->getMouseLButton()) {
			console->setLogText("saving file...");
			saveEditorLevelToFile();
			dirty = false;
		}
	}

	// BRUSH buttons
	for (int i = 0; i < brushSelectorButtonList.size(); i++) {
		BlockButton* it = &brushSelectorButtonList.at(i); // is a pointer needed/best?
		if (it) {
			if (it->isMouseOver()) {
				if (input->getMouseLButton()) {
					setCurrentButtonBrush(it); // there can be only one
					break;
				}
			}
		}
	}

	// handle mouseover for all game blocks
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks.at(i).isMouseOver()) {
			if (input->getMouseLButton()) {
				blocks.at(i).changeBlockType(currentType);
				dirty = true;
			}
			if (input->getMouseRButton()) {
				// right click resets
				blocks.at(i).changeBlockType(NONE);
				dirty = true;
			}
		}
	}

	console->setLogText(dirty ? "unsaved changes" : "up to date");

}

void Editor::draw()
{
	for (auto it : textButtonList) {
		it->draw();
	}

	if (dirty) {
		saveButton.setFontColor(graphicsNS::WHITE);
	}

	saveButton.draw();

	// draw brush selector buttons
	for (int i = 0; i < brushSelectorButtonList.size(); i++) {
		brushSelectorButtonList.at(i).draw(true);
	}

	// draw each level block button
	for (int i = 0; i < blocks.size(); i++) {
		blocks.at(i).draw();
	}

	console->renderLog();
}

/// <summary>
/// Converts Level raw BLOCK enum data into BlockButtons
/// </summary>
/// <param name="level"></param>
void Editor::loadCurrentEditorLevel()
{
	Level loadedLevel;
	FileHandler handler;

	if (handler.loadLevelFromFile(loadedLevel, currentLevel))
	{
		editLevel(loadedLevel);
	}

}

/// <summary>
/// Takes currently loaded level data and displays buttons for actual editing
/// </summary>
/// <param name="level"></param>
void Editor::editLevel(Level level)
{
	constexpr int START_X = 114;
	constexpr int START_Y = 100;

	blocks.clear();

	// load up vector with blocks from the level data
	int y = START_Y;
	for (int i = 0; i < ROWS; i++) {

		int x = START_X;
		for (int j = 0; j < COLS; j++) {

			BlockButton newBlock(level.data.at(i * COLS + j));

			if (!newBlock.initialize(game, blockNS::WIDTH, blockNS::HEIGHT, blockNS::TEXTURE_COLS, blockTexture))
			{
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block entity"));
			}

			newBlock.setPosition(x, y);

			// add to vector
			blocks.push_back(newBlock);

			// move to the right
			x += blockNS::WIDTH;
		}

		// set new row downward
		y += blockNS::HEIGHT;
	}
}

/// <summary>
/// Save changes to file.
/// </summary>
void Editor::saveEditorLevelToFile()
{
	FileHandler handler;
	handler.saveLevelToDisk(blocks, COLS, currentLevel);
}
