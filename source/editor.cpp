#include "editor.h"
#include <fstream>
#include <iostream>
using namespace std;

Editor::Editor()
{
    dirty = false;
    currentType = WEAK;
}

Editor::~Editor()
{
}

bool Editor::initialize(Game* pGame, TextureManager* textButtonTexM, TextureManager* blockTexM, Console* pCons)
{
    input = pGame->getInput();
    game = pGame;
    blockTexture = blockTexM;

    // text button
    if (!saveButton.initialize(game, 200, 64, 0, textButtonTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text button image"));
        return false;
    }

    saveButton.setText("SAVE LEVEL");
    saveButton.setX(GAME_WIDTH / 2 - saveButton.getSpriteData().width / 2);
    saveButton.setY(500);
    // set the font draw rect inside the button
    saveButton.calculateDrawRect();
    
    // regular button
    if (!weakButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }

    weakButton.setX(100);
    weakButton.setY(400);

    // regular button
    if (!strongButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }

    strongButton.setX(weakButton.getX() + strongButton.getWidth() + 10);
    strongButton.setY(400);
    strongButton.changeBlockType(STRONG);

    // regular button
    if (!hardButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }

    hardButton.setX(strongButton.getX() + hardButton.getWidth() + 10);
    hardButton.setY(400);
    hardButton.changeBlockType(HARD);

    // regular button
    if (!metalButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }

    metalButton.setX(hardButton.getX() + metalButton.getWidth() + 10);
    metalButton.setY(400);
    metalButton.changeBlockType(METAL);

    // regular button
    if (!invincibleButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }

    invincibleButton.setX(metalButton.getX() + invincibleButton.getWidth() + 10);
    invincibleButton.setY(400);
    invincibleButton.changeBlockType(INVINCIBLE);

    // set up console
    console = pCons;
    console->setLogText("EDITOR MODE");

    return true;
}

void Editor::update()
{
    if (saveButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            console->setLogText("saving file...");
            saveEditorLevelToFile();
            dirty = false;
        }
    }
    if (weakButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            currentType = WEAK;
        }
    }
    if (strongButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            currentType = STRONG;
        }
    }
    if (hardButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            currentType = HARD;
        }
    }
    if (metalButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            currentType = METAL;
        }
    }
    if (invincibleButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            currentType = INVINCIBLE;
        }
    }

    // seems bizarre that it works within update()
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
    // draw UI buttons
    saveButton.draw();
    weakButton.draw();
    strongButton.draw();
    hardButton.draw();
    metalButton.draw();
    invincibleButton.draw();
    
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
void Editor::loadEditorLevel(Level level)
{
    const float START_X = 114;
    const float START_Y = 100;
    
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

            newBlock.setX(x);
            newBlock.setY(y);

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
/// Writes out blocks vector to file, line by line, to match Level file format
/// </summary>
void Editor::saveEditorLevelToFile()
{
    // write this shit to disk
    ofstream out("EditorLevelSave.txt"); //open existing file
    if (out.is_open()) {
        //
        out << "2255\n";
        out << "EDITOR SAVE\n";

        for (int i = 0; i < blocks.size(); i++) {
            out << blocks.at(i).getBLockType() << "\n";
            if (i == COLS || i == COLS*2) {
                out << "// new row \n";
            }
        }
    }

    out.close();
}
