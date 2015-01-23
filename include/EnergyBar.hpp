#ifndef ENERGYBAR_HPP
#define ENERGYBAR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "PEvent.hpp"
#include "Debug.hpp"

#define BAR_WIDTH 100.0
#define BAR_HEIGHT 25.0
#define BAR_BORDER_MULT 1.1

using namespace sf;
using namespace std;

class Player;

class EnergyBar : public GameObject
{
public:
    EnergyBar(Player *p);

    Player *attachedPlayer;
    RectangleShape rectBorder, rectEnergy;


    virtual void onUpdate(float dt);
    virtual void onDraw(RenderTarget& target, const Transform& transform);
};

#endif // ENERGYBAR_HPP
