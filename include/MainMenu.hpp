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
    static float c;
    static Shader *shad;
    MainMenu();
    virtual void onKeyDown(PEvent &e);
    virtual void onUpdate(float dt);
};

#endif // MAINMENU_H
