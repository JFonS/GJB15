#include "../include/Block.hpp"

Texture* Block::noiseTex = nullptr;
//Shader* Block::shad = nullptr;

Block::Block(int type)
{
    if(noiseTex == nullptr)
    {
        noiseTex = new Texture();
        noiseTex->loadFromFile("assets/noise.png");
    }

    noiseCoords = Vector2f(float(rand() % 1000)/1200, float(rand() % 1000)/1200);
    noiseAlpha = float(rand()%100)/300 + 0.1f;


    if(isDoor(type))
    {
        noiseCoords = Vector2f(0.5f, 0.5f);
        noiseAlpha = 0.3f;
    }
    else if(type == DEATH)
    {
        noiseCoords = Vector2f(0.5f, 0.5f);
        noiseAlpha = 0.3f;
    }

    enabled = true;
    this->type = type;

    /*if(shad == nullptr)
    {
        shad = new Shader();
        shad->loadFromFile("assets/noiseFrag", Shader::Fragment);
    }*/
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

        if (isButton(GetType()) || isPalanca(GetType()) || isPortal(GetType())) enabled = false;
        else if(GetType() == DEATH) l->Reset();
    }
    else if (isButton(GetType())) enabled = true;

    if(GetType() == FINISH)
    {
        if(touchingPlayer1) l->player1->levelCompleted = true;
        else if(touchingPlayer2) l->player2->levelCompleted = true;
    }

    if(l->player1->levelCompleted && l->player2->levelCompleted) l->Complete();
}

void Block::onDraw(RenderTarget& target, const Transform& transform)
{
    Level *l = (Level*) PeezyWin::peekScene();
    /*shad->setParameter("tex", *getTexture());
    shad->setParameter("noiseTex", *noiseTex);
    shad->setParameter("isBG", 0.0f);
    shad->setParameter("noiseCoords", noiseCoords);
    shad->setParameter("alpha", noiseAlpha);
    Vector2f p2Center = Vector2f(l->player2->getGlobalBounds().left + l->player2->getGlobalBounds().width/2, PeezyWin::winHeight - (l->player2->getGlobalBounds().top + l->player2->getGlobalBounds().height/2));
    Vector2f p1Center = Vector2f(l->player1->getGlobalBounds().left + l->player1->getGlobalBounds().width/2, PeezyWin::winHeight - (l->player1->getGlobalBounds().top + l->player1->getGlobalBounds().height/2));
    shad->setParameter("p1", l->camera.getInverse() * p1Center);
    shad->setParameter("p2", l->camera.getInverse() * p2Center);*/
    if(isDoor(type))
    {
        bool nothing = true;
        for(Block *b : l->blocks)
        {
            if(!b->enabled && (isPalanca(b->GetType()) || isButton(b->GetType())) &&
               getObjectIndex(type) == getObjectIndex(b->GetType()))
            {
                enabled = nothing = false;
            }
        }
        if(nothing) enabled = true; //cerramos puerta
    }

    RenderStates rs;
    rs.transform = transform;
    //if(type != LIGHT) rs.shader = shad;
    if( !(isDoor(type) && !enabled) ) target.draw(*this, rs);

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

int Block::getObjectIndex(int type)
{
    if (isDoor(type)) return type - DOOR_START;
    if (isPalanca(type)) return type - PALANCA_START;
    if (isButton(type)) return type - BUTTON_START;
    if (isPortal(type)) return type - PORTAL_START;
    return -1;
}
