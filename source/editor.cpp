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
}

Editor::~Editor()
{
    // I feel like there should be stuff to do here
}

bool Editor::initialize(Game* pGame, TextureManager* textButtonTexM, TextureManager* blockTexM, Console* pCons)
{
    constexpr int buttonSpacing = 106;
    constexpr int buttonY = 400;
    input = pGame->getInput();
    game = pGame;
    blockTexture = blockTexM;

    /// UI BUTTONS
    if (!weakButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }
    weakButton.setPosition(160, buttonY);

    if (!strongButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }
    strongButton.setPosition(weakButton.getX() + buttonSpacing, buttonY);
    strongButton.changeBlockType(STRONG);

    if (!hardButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }
    hardButton.setPosition(GAME_WIDTH / 2 - hardButton.getWidth() / 2, buttonY);
    hardButton.changeBlockType(HARD);

    if (!metalButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }
    metalButton.setPosition(hardButton.getX() + buttonSpacing, buttonY);
    metalButton.changeBlockType(METAL);

    if (!invincibleButton.initialize(game, 64, 64, 0, blockTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blockbutton image"));
        return false;
    }
    invincibleButton.setPosition(metalButton.getX() + buttonSpacing, buttonY);
    invincibleButton.changeBlockType(INVINCIBLE);

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

    // build UI list
    setCurrentButtonBrush(&weakButton);
    selectorButtonList.push_back(&weakButton);
    selectorButtonList.push_back(&strongButton);
    selectorButtonList.push_back(&hardButton);
    selectorButtonList.push_back(&metalButton);
    selectorButtonList.push_back(&invincibleButton);

    // set up console
    console = pCons;
    console->setLogText("EDITOR MODE");

    return true;
}

void Editor::setCurrentButtonBrush(BlockButton* btn) {
    // set new current brush
    currentType = btn->getBlockType();
    btn->setSelected(true);

    // reset all other buttons
    for (int i = 0; i < selectorButtonList.size(); i++) {
        // does this work?
        if (btn != selectorButtonList.at(i)) {
            selectorButtonList.at(i)->setSelected(false);
        }
    }
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
    
    // deal with brush buttons
    for (int i = 0; i < selectorButtonList.size(); i++) {
        BlockButton* it = selectorButtonList.at(i);
        if (it->isMouseOver()) {
            if (input->getMouseLButton()) {
                setCurrentButtonBrush(it); // there can be only one
                break;
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
    saveButton.draw();
    
    // draw brush selector buttons
    for (int i = 0; i < selectorButtonList.size(); i++) {
        selectorButtonList.at(i)->draw();
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
void Editor::loadEditorLevel(Level level)
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
