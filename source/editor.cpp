#include "editor.h"
#include <fstream>
#include <iostream>
using namespace std;

Editor::Editor()
{
    dirty = false;
}

Editor::~Editor()
{
    //SAFE_DELETE(console);
    //SAFE_DELETE(input);
    // save button has dx font and image.. image texture is 
}

bool Editor::initialize(Game* pGame, TextureManager* textButtonTexM, TextureManager* bTexM, Console* pCons)
{
    input = pGame->getInput();
    game = pGame;
    blockTexture = bTexM;

    // text button
    if (!saveButton.initialize(game, 200, 64, 0, textButtonTexM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text button image"));
        return false;
    }

    saveButton.setText("SAVE LEVEL");
    saveButton.setX(GAME_WIDTH / 2 - saveButton.getSpriteData().width);
    saveButton.setY(500);
    // set the font draw rect inside the button
    saveButton.calculateDrawRect();

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

    // seems bizarre that it works within update()
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks.at(i).isMouseOver()) {
            if (input->getMouseLButton()) {
                blocks.at(i).changeBlockType();
                dirty = true;
            }
        }
    }

    console->setLogText(dirty ? "unsaved changes" : "up to date");

}

void Editor::draw()
{
    saveButton.draw();
    
    // draw each button
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
