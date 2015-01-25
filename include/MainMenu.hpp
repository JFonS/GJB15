#ifndef MAINMENU_H
#define MAINMENU_H


#include "Scene.hpp"
#include "MovieClip.hpp"
#include "PeezyWin.hpp"

using namespace std;
using namespace sf;

class MainMenu : public Scene
{
public:
    MainMenu();
    virtual void onKeyDown(PEvent &e);
};

#endif // MAINMENU_H
