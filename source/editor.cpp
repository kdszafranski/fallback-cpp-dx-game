#include "editor.h"

Editor::Editor()
{
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
    if (input->wasKeyPressed(SPACE_KEY)) {
            console->setLogText("clicked to save");
        }
    if (saveButton.isMouseOver()) {
    }
}

void Editor::draw()
{
    saveButton.draw();
    console->renderLog();
}

void Editor::loadEditorLevel()
{

}
