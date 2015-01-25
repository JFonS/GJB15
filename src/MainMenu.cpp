#include "../include/MainMenu.hpp"

float MainMenu::c = 0.0f;
Shader* MainMenu::shad = nullptr;

MainMenu::MainMenu() : Scene("mainMenu")
{
    if(shad == nullptr)
    {
        shad = new Shader();
        shad->loadFromFile("assets/mainMenuFrag", Shader::Fragment);
    }

    GameObject *menuBG = new GameObject("menuBG");
    menuBG->setTexture("assets/menu.png");

    PeezyWin::menuMusic.play();
    ButtonText *playButton = new ButtonText();
    playButton->setString("PLAY");
    float w = playButton->getGlobalBounds().width;
    playButton->setPosition(PeezyWin::winWidth/2-w/2, PeezyWin::winHeight/2);
    playButton->downFunction = [](){
        PeezyWin::changeScene(PeezyWin::intro);
        PeezyWin::menuMusic.stop();
        PeezyWin::gameMusic.play();
    };

    addChild(playButton);
    addChild(menuBG);

    menuBG->setIndex(-1);
}

void MainMenu::onKeyDown(PEvent &e)
{
    if(e.key.code == Keyboard::Space)
    {
        PeezyWin::changeScene(PeezyWin::intro);
        PeezyWin::menuMusic.stop();
        PeezyWin::gameMusic.play();
    }
}

void MainMenu::onUpdate(float dt)
{
    c += dt;
}
