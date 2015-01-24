#ifndef MOVIECLIP_H
#define MOVIECLIP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "PEvent.hpp"
#include "Debug.hpp"

using namespace std;
using namespace sf;

class MovieClip : public GameObject
{
protected:

    vector<Texture*> textures;
    map<string, int> keyFrames;

    string currentKeyFrame;
    float timeSinceLastFrame;
    bool playing;

public:
    int currentFrame;
    float timePerFrame;
    MovieClip();
    virtual ~MovieClip();

    void loadSpriteSheet(string sspath, int nFrames);
    void addFrame(string path);
    void addKeyFrame(int n, string keyFrameName);

    virtual void onUpdate(float dt){};

    void update(float dt);

    void gotoAndPlay(string keyFrameName);
    void gotoAndStop(string keyFrameName);
    void play();
    void stop();

    virtual void onKeyDown(PEvent &e);
    virtual void onMouseEnter(PEvent &e);
    virtual void onMouseExit(PEvent &e);
    virtual void onMouseOver();

    int getKeyFrameNum(string keyFrameName);

};

#endif // MOVIECLIP_H
