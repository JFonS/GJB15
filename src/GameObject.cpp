#include "../include/GameObject.hpp"
#include "../include/Block.hpp"
#include <stdlib.h>

GameObject::GameObject(): textureName("none") {
  name = "none";
  zIndex = 0;
}

GameObject::GameObject(string n): textureName("none") {
  name = n;
  zIndex = 0;
}

GameObject::~GameObject()
{
  ResourceManager::deleteTexture(textureName);
}

void GameObject::setTexture(string texture)
{
  ResourceManager::deleteTexture(textureName);
  Sprite::setTexture(ResourceManager::getTexture(texture));
  textureName = texture;
}

void GameObject::onDraw(RenderTarget& target, const Transform& transform)
{
    if(name == "bg" && Block::shad != nullptr)
    {
        Level *l = (Level*) PeezyWin::peekScene();
        Block::shad->setParameter("tex", *getTexture());
        Block::shad->setParameter("noiseTex", *Block::noiseTex);
        Block::shad->setParameter("isBG", 1.0f);
        Vector2f noiseCoords = Vector2f(0.0f, 0.0f);
        Block::shad->setParameter("noiseCoords", noiseCoords);
        Block::shad->setParameter("alpha", 0.3f);
        Vector2f p2Center = Vector2f(l->player2->getGlobalBounds().left + l->player2->getGlobalBounds().width/2, PeezyWin::winHeight - (l->player2->getGlobalBounds().top + l->player2->getGlobalBounds().height/2));
        Vector2f p1Center = Vector2f(l->player1->getGlobalBounds().left + l->player1->getGlobalBounds().width/2, PeezyWin::winHeight - (l->player1->getGlobalBounds().top + l->player1->getGlobalBounds().height/2));
        Block::shad->setParameter("p1", l->camera.getInverse() * p1Center);
        Block::shad->setParameter("p2", l->camera.getInverse() * p2Center);

        RenderStates rs;
        rs.transform = transform;
        rs.shader = Block::shad;
        target.draw(*this, rs);
    }
    else if(name == "menuBG")
    {
        RenderStates rs;
        rs.transform = transform;
        if(MainMenu::shad != nullptr)
        {
            rs.shader = MainMenu::shad;
            MainMenu::shad->setParameter("tex", *getTexture());
            MainMenu::shad->setParameter("time", Level::c);
            MainMenu::shad->setParameter("mousePos", Vector2f(Mouse::getPosition(*PeezyWin::window).x, PeezyWin::winHeight - Mouse::getPosition().y + 50.0f));
        }
        target.draw(*this, rs);
    }
    else target.draw(*this, transform);
}

const Transform & GameObject::getNodeTransform() { return Sprite::getTransform();}

Rect<float> GameObject::getBoundingBox()
{
    return getLocalBounds();
}

void GameObject::onUpdate(float dt){}

void GameObject::onKeyDown(PEvent &e) {}

void GameObject::onMouseEnter(PEvent &e){}

void GameObject::onMouseExit(PEvent &e){}

void GameObject::onMouseOver(){}
