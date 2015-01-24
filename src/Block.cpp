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
    if(isDoor(type))
    {
        enabled = !Level::buttonPressed;
    }

    if(enabled || isPalanca(type)) {
        GameObject::onDraw(target, transform);
    }

    if(isPalanca(type) && enabled)
    {
        Sprite::setTexture(ResourceManager::getTexture("assets/interruptorof.png"));
    }
    else if(isPalanca(type) && !enabled)
    {
        Sprite::setTexture(ResourceManager::getTexture("assets/interruptoron.png"));
    }
}

int Block::GetType()
{
    return type;
}

int Block::getObjectIndex(int n) {
    if (isDoor(n)) return n - DOOR_START;
    if (isPalanca(n)) return n - PALANCA_START;
    if (isButton(n)) return n - BUTTON_START;
    return -1;
}
