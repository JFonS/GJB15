#include "../include/MovieClip.hpp"

MovieClip::MovieClip()
{
    currentFrame = 0;
    timePerFrame = 0.5f;
    timeSinceLastFrame = 0.0f;
    playing = false;
    currentKeyFrame = "";
}

MovieClip::~MovieClip()
{
    for(auto t : textures)
    {
        ResourceManager::deleteTexture(t);
    }
}

void MovieClip::loadSpriteSheet(string sspath, int nFrames)
{
    Image img = Image();
    img.loadFromFile(sspath);

    int stride = img.getSize().x / nFrames;
    Rect<int> tileImgFrame(0, 0, stride, img.getSize().y);
    for(int i = 0; i < nFrames; ++i)
    {
        textures.push_back(new Texture());
        textures[i]->loadFromImage(img, tileImgFrame);
        tileImgFrame = Rect<int>(tileImgFrame.left + stride, 0, stride, img.getSize().y);
    }
    Sprite::setTexture(*textures[0]);
}

void MovieClip::update(float dt)
{
    GameObject::update(dt);
    timeSinceLastFrame += dt;
    if(timeSinceLastFrame > timePerFrame)
    {
        timeSinceLastFrame = 0;
        if(playing)
        {
            Sprite::setTexture(*textures[currentFrame]);
            ++currentFrame;
            if(currentFrame >= int(textures.size())) {
                if(currentKeyFrame == "") currentFrame = 0;
                else currentFrame = keyFrames[currentKeyFrame];
            }
            else if(currentKeyFrame != "" && currentFrame > keyFrames["F" + currentKeyFrame])
            {
                currentFrame = keyFrames[currentKeyFrame];
            }
        }
    }
    if(!playing) timeSinceLastFrame = 0;
}

void MovieClip::addKeyFrame(int n, string keyFrameName)
{
    keyFrames[keyFrameName] = n;
}

void MovieClip::gotoAndPlay(string keyFrameName)
{
    currentFrame = getKeyFrameNum(keyFrameName);
    currentKeyFrame = keyFrameName;
    play();
}

void MovieClip::gotoAndStop(string keyFrameName)
{
    currentFrame = getKeyFrameNum(keyFrameName);
    currentKeyFrame = keyFrameName;
    stop();
}

void MovieClip::play()
{
    playing = true;
}

void MovieClip::stop()
{
    playing = false;
}

int MovieClip::getKeyFrameNum(string keyFrameName)
{
    return keyFrames[keyFrameName];
}

void MovieClip::onKeyDown(PEvent &e) {}

void MovieClip::onMouseEnter(PEvent &e){}

void MovieClip::onMouseExit(PEvent &e){}

void MovieClip::onMouseOver(){}
