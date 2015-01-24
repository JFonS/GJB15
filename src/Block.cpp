#include "../include/Block.hpp"

Block::Block(int type)
{
    enabled = true;
    this->type = type;
}

Block::~Block()
{
}

void Block::onUpdate(float dt)
{
}

void Block::onDraw(RenderTarget& target, const Transform& transform)
{
    if(type == DOOR)
    {
        enabled = !Level::buttonPressed;
    }

    if(enabled) {
        GameObject::onDraw(target, transform);
    }
}

int Block::GetType()
{
    return type;
}
