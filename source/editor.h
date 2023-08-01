#pragma once
#include "constants.h"
#include "textButton.h"
#include "console.h"
#include "block.h"
#include "level.h"
#include <vector>

class Editor
{
private:
	std::vector<Block>* blocks;
	Graphics* graphics;	// shared with Fallback
	Input* input;		// shared with Fallback
	TextButton saveButton;
	Console* console;	// shared with Fallback
	int test;

public:
	Editor();
	~Editor();
	bool initialize(Game* pGame, TextureManager* textureM, Console* pCons);

	void update();
	void draw();
	void loadEditorLevel(Level level);
};

