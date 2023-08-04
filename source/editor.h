#pragma once
#include "constants.h"
#include "textButton.h"
#include "console.h"
//#include "block.h"
#include "blockButton.h"
#include "level.h"
#include <vector>

class Editor
{
private:
	bool dirty;
	const int COLS = 9;
	const int ROWS = 3;
	BLOCK currentType;
	
	std::vector<BlockButton> blocks;
	std::vector<BlockButton*> selectorButtonList;
	
	Game* game;
	Input* input;		// shared with Fallback
	TextureManager* blockTexture;
	Console* console;	// shared with Fallback

	// UI Buttons
	TextButton saveButton;
	BlockButton weakButton;
	BlockButton strongButton;
	BlockButton hardButton;
	BlockButton metalButton;
	BlockButton invincibleButton;

public:
	Editor();
	~Editor();
	bool initialize(Game* pGame, TextureManager* textButtonTexM, TextureManager* bTexM, Console* pCons);

	void update();
	void draw();
	void loadEditorLevel(Level level);
	void saveEditorLevelToFile();
	void setCurrentButtonBrush(BlockButton* btn);
};

