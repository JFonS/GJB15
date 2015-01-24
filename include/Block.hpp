#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Level.hpp"
#include "ResourceManager.hpp"
#include "MovieClip.hpp"
#include "PEvent.hpp"
#include "Debug.hpp"

#define SOLID 1
#define BUTTON 2
#define DEATH 3
#define PALANCA 4
#define DOOR 6

class Block : public GameObject
{
private:
    int type;

public:
    bool enabled;

    Block(int type);
    virtual ~Block();

    int GetType();
    virtual void onUpdate(float dt);
    virtual void onDraw(RenderTarget& target, const Transform& transform);
};

#endif // BLOCK_HPP
