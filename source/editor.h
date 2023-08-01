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
	std::vector<BlockButton> blocks;
	BLOCK currentType;
	Game* game;
	Input* input;		// shared with Fallback
	TextureManager* blockTexture;
	Console* console;	// shared with Fallback
	bool dirty;
	const int COLS = 9;
	const int ROWS = 3;

	// UI
	TextButton saveButton;
	TextButton weakButton;
	TextButton strongButton;

public:
	Editor();
	~Editor();
	bool initialize(Game* pGame, TextureManager* textButtonTexM, TextureManager* bTexM, Console* pCons);

	void update();
	void draw();
	void loadEditorLevel(Level level);
	void saveEditorLevelToFile();
};

