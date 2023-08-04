#pragma once
#include "constants.h"
#include "textButton.h"
#include "console.h"
//#include "block.h"
#include "blockButton.h"
#include "level.h"
#include <vector>
#include <memory>

typedef std::vector<std::shared_ptr<TextButton>> TextButtonList;
class Editor
{
private:
	bool dirty;
	const int COLS = 9;
	const int ROWS = 3;
	BLOCK currentType;
	int currentLevel;
	
	std::vector<BlockButton> blocks;
	std::vector<BlockButton> brushSelectorButtonList;
	TextButtonList textButtonList;
	
	Game* game;
	Input* input;		// shared with Fallback
	TextureManager* blockTexture;
	Console* console;	// shared with Fallback

	// UI Buttons
	TextButton saveButton;
	//TextButton level0Button;
	//TextButton level1Button;

public:
	Editor();
	~Editor();
	bool initialize(Game* pGame, TextureManager* textButtonTexM, TextureManager* bTexM, Console* pCons);
	void start();

	void update();
	void draw();
	void loadCurrentEditorLevel();
	void editLevel(Level level);
	void saveEditorLevelToFile();
	void setCurrentButtonBrush(BlockButton* btn);
};

