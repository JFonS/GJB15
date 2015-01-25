#include "../include/MainMenu.hpp"

MainMenu::MainMenu() : Scene("mainMenu")
{
    GameObject *menuBG = new GameObject("menuBG");
    menuBG->setTexture("assets/menu.png");

    ButtonText *playButton = new ButtonText();
    playButton->setString("PLAY");
    float w = playButton->getGlobalBounds().width;
    playButton->setPosition(PeezyWin::winWidth/2-w/2, PeezyWin::winHeight/2);
    playButton->downFunction = [](){PeezyWin::changeScene(PeezyWin::intro);};

    addChild(playButton);
    addChild(menuBG);

    menuBG->setIndex(-1);
}

void MainMenu::onKeyDown(PEvent &e)
{
    if(e.key.code == Keyboard::Space)
    {
        PeezyWin::changeScene(PeezyWin::intro);
    }
}
