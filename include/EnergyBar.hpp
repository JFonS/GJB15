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

#define BAR_WIDTH 100.0f
#define BAR_HEIGHT 25.0f
#define BAR_BORDER_THICKNESS 3.0f

using namespace sf;
using namespace std;

class Player;

class EnergyBar : public GameObject
{
public:

    Player *attachedPlayer;
    RectangleShape rectBorder, rectEnergy;

    EnergyBar(Player *p);

    virtual void onUpdate(float dt);
    virtual void onDraw(RenderTarget& target, const Transform& transform);
};

#endif // ENERGYBAR_HPP
