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
    if(isButton(GetType()))
    {
        Level *l = (Level*) PeezyWin::peekScene();
        if(l->player1->hitting(this) || l->player2->hitting(this))
        {
            enabled = false;
        }
        else enabled = true;
    }
}

void Block::onDraw(RenderTarget& target, const Transform& transform)
{
    Level *l = (Level*) PeezyWin::peekScene();

    if(isButton(type) && !enabled)
    {
        for(Block *b : l->blocks)
        {
            if(isDoor(b->GetType()) && getObjectIndex(GetType()) == getObjectIndex(b->GetType()))
            {
                b->enabled = false;
            }
        }
    }
    else if(isButton(type))
    {
        for(Block *b : l->blocks)
        {
            if(isDoor(b->GetType()) && getObjectIndex(GetType()) == getObjectIndex(b->GetType()))
            {
                b->enabled = true;
            }
        }
    }

    if(isPalanca(type) && !enabled)
    {
        for(Block *b : l->blocks)
        {
            if(isDoor(b->GetType()) && getObjectIndex(GetType()) == getObjectIndex(b->GetType()))
            {
                b->enabled = false;
            }
        }
    }

    if(enabled || isPalanca(type) || isButton(type))
    {
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

int Block::getObjectIndex(int type) {
    if (isDoor(type)) return type - DOOR_START;
    if (isPalanca(type)) return type - PALANCA_START;
    if (isButton(type)) return type - BUTTON_START;
    return -1;
}
