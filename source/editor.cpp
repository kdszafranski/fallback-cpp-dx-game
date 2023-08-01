#include "editor.h"

Editor::Editor()
{
    test = 0;
}

Editor::~Editor()
{
    //SAFE_DELETE(console);
    //SAFE_DELETE(input);
    // save button has dx font and image.. image texture is 
}

bool Editor::initialize(Game* pGame, TextureManager* textureM, Console* pCons)
{
    input = pGame->getInput();

    // text button
    if (!saveButton.initialize(pGame, 200, 64, 0, textureM))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text button image"));
        return false;
    }

    saveButton.setText("SAVE LEVEL");
    saveButton.setX(GAME_WIDTH/2 - saveButton.getSpriteData().width);
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
            console->setLogText("clicked button");
        }
    }
}

void Editor::draw()
{
    saveButton.draw();
    
    // d
    for (int i = 0; i < blocks->size(); i++) {
        blocks->at(i).draw();
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
    const int COLS = 9;
    const int ROWS = 3;

    //blocks.clear();

    //// load up vector with blocks from the level data
    //int y = START_Y;
    //for (int i = 0; i < ROWS; i++) {

    //    int x = START_X;
    //    for (int j = 0; j < COLS; j++) {

    //        if (levels.at(levelNumber).data.at(i * COLS + j) == NONE) {
    //            // skip
    //        } else {
    //            Block newBlock(levels.at(levelNumber).data.at(i * COLS + j));

    //            if (!newBlock.initialize(this, blockNS::WIDTH, blockNS::HEIGHT, blockNS::TEXTURE_COLS, &blockTexture))
    //            {
    //                throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block entity"));
    //            }

    //            newBlock.setX(x);
    //            newBlock.setY(y);
    //            newBlock.setVelocity(VECTOR2(0, 0));

    //            // add to vector
    //            blocks.push_back(newBlock);
    //        }

    //        // move to the right
    //        x += blockNS::WIDTH;
    //    }

    //    // set new row downward
    //    y += blockNS::HEIGHT;
    //}
}
