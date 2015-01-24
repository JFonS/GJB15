#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Level.hpp"
#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "PEvent.hpp"
#include "Debug.hpp"

#define SOLID 1
#define BUTTON 2
#define DOOR 3

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
