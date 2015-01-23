#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "PEvent.hpp"
#include "Debug.hpp"

class Block : public GameObject
{
public:
    Block();
    virtual ~Block();

    virtual void onUpdate(float dt);
};

#endif // BLOCK_HPP
