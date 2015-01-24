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
    Level *l = (Level*) PeezyWin::peekScene();
    bool touchingPlayer1 = l->player1->hitting(this), touchingPlayer2 = l->player2->hitting(this);
    if(touchingPlayer1 || touchingPlayer2)
    {
        if(isPortal(GetType()))
        {
            if(enabled) //Per evitar bucle infinito de portal
            {
                Block *destinyPortal = nullptr;
                for(Block *b : l->blocks)
                {
                    if(this != b && isPortal(b->GetType()) &&
                       getObjectIndex(GetType()) == getObjectIndex(b->GetType()))
                    {
                        destinyPortal = b;
                        break;
                    }
                }

                if(destinyPortal != nullptr)
                {
                    if(touchingPlayer1) l->player1->gotoPortal(destinyPortal);
                    else l->player2->gotoPortal(destinyPortal);
                }
            }
        }

        if (isButton(GetType()) || isPalanca(GetType()) || isPortal(GetType())) enabled = false;
        else if(GetType() == DEATH) l->Reset();
    }
    else if ( isButton(GetType()) || isPortal(GetType()) ) enabled = true;
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
    if (isPortal(type)) return type - PORTAL_START;
    return -1;
}
