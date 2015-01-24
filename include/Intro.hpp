#ifndef INTRO_HPP
#define INTRO_HPP

#include "Scene.hpp"
#include "MovieClip.hpp"
using namespace std;
using namespace sf;

class Intro: public Scene {
private:
    Intro();
    void onUpdate();
    MovieClip introClip;
};

#endif // INTRO_HPP
