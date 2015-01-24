#ifndef INTRO_HPP
#define INTRO_HPP

#include "Scene.hpp"
#include "MovieClip.hpp"
#include "PeezyWin.hpp"

using namespace std;
using namespace sf;

class Intro: public Scene
{
public:
    Intro();
    virtual void onUpdate(float dt);
    virtual void onKeyDown(PEvent &e);
    MovieClip *introClip;
};

#endif // INTRO_HPP
