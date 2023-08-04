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
    //SAFE_DELETE(game);
    //SAFE_DELETE(input);
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
    saveButton.setText("SAVE LEVEL");
    saveButton.setPosition(GAME_WIDTH / 2 - saveButton.getSpriteData().width / 2, 500);
    // set the font draw rect inside the button
    saveButton.calculateDrawRect();

    // set up console
    console = pCons;
    console->setLogText("EDITOR MODE");

    return true;
}

void Editor::setCurrentButtonBrush(BlockButton &btn) {
    currentType = btn.getBlockType();
    btn.setSelected(true);
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
            setCurrentButtonBrush(weakButton);
        }
    }
    if (strongButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            setCurrentButtonBrush(strongButton);
        }
    }
    if (hardButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            setCurrentButtonBrush(hardButton);
        }
    }
    if (metalButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            setCurrentButtonBrush(metalButton);
        }
    }
    if (invincibleButton.isMouseOver()) {
        if (input->getMouseLButton()) {
            setCurrentButtonBrush(invincibleButton);
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
/// Writes out blocks vector to file, line by line, to match Level file format
/// </summary>
void Editor::saveEditorLevelToFile()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    std::string timeStamp = std::to_string(st.wYear);
    timeStamp += "." + std::to_string(st.wMonth) + "." + std::to_string(st.wDay);
    timeStamp += "-" + std::to_string(st.wHour) + ":" + std::to_string(st.wMinute) + ":" + std::to_string(st.wSecond);
    

    // write this shit to disk
    ofstream out("Level0.txt"); //open existing file
    if (out.is_open()) {
        //
        out << timeStamp;
        out << "\n";
        out << "EDITOR SAVE\n";

        for (int i = 0; i < blocks.size(); i++) {
            out << blocks.at(i).getBlockType() << "\n";
            // 0-8 row 1
            // 9-17 row 2
            // 18-26 row 3
            if (i == COLS - 1 || i == COLS * 2 - 1) {
                out << "// new row " << i << "\n";
            }
        }
    }

    out.close();
}
