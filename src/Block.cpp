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

    if(enabled || type == PALANCA) {
        GameObject::onDraw(target, transform);
    }

    if(type == PALANCA && enabled)
    {
        Sprite::setTexture(ResourceManager::getTexture("assets/interruptorof.png"));
    }
    else if(type == PALANCA && !enabled)
    {
        Sprite::setTexture(ResourceManager::getTexture("assets/interruptoron.png"));
    }
}

int Block::GetType()
{
    return type;
}
