#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "PEvent.hpp"
#include "Debug.hpp"

#define SOLID 1

class Block : public GameObject
{
private:
    int type;

public:
    Block(int type);
    virtual ~Block();

    int GetType();
    virtual void onUpdate(float dt);
};

#endif // BLOCK_HPP
