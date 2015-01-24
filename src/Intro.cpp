#include "../include/Intro.hpp"

Intro::Intro() : Scene("intro")
{
    introClip = new MovieClip();
    introClip->addFrame("assets/intro/1.png");
    introClip->addFrame("assets/intro/2.png");
    introClip->addFrame("assets/intro/3.png");
    introClip->addFrame("assets/intro/4.png");
    introClip->addFrame("assets/intro/5.png");
    introClip->addFrame("assets/intro/6.png");
    introClip->addFrame("assets/intro/6.png");
    introClip->timePerFrame = 4.0f;
    introClip->currentFrame = 0;
    introClip->play();

    addChild(introClip);
}

void Intro::onUpdate(float dt) {
    if (introClip->currentFrame == 6)
        PeezyWin::changeScene(PeezyWin::level1);
}

void Intro::onKeyDown(PEvent &e) {
    if(e.key.code == Keyboard::Space)
    {
        PeezyWin::changeScene(PeezyWin::level1);
    }
}
