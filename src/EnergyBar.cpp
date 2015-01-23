#include "../include/EnergyBar.hpp"

EnergyBar::EnergyBar(Player *p) : GameObject()
{
    attachedPlayer = p;
    rectBorder = RectangleShape(Vector2f(BAR_WIDTH * BAR_BORDER_MULT, BAR_HEIGHT * BAR_BORDER_MULT));
    rectBorder.setFillColor(Color::White);
    rectEnergy = RectangleShape(Vector2f(BAR_WIDTH, BAR_HEIGHT));
    rectEnergy.setFillColor(Color::Green);

    rectBorder.setPosition(BAR_WIDTH - 50.0f, attachedPlayer->isPlayerOne ? 50.0f : 400.0f);
    rectEnergy.setPosition(BAR_WIDTH - 50.0f, attachedPlayer->isPlayerOne ? 50.0f : 400.0f);
}

void EnergyBar::onUpdate(float dt)
{
    rectBorder = (attachedPlayer->energy / attachedPlayer->maxEnergy) * BAR_WIDTH * BAR_BORDER_MULT;
    rectEnergy = (attachedPlayer->energy / attachedPlayer->maxEnergy) * BAR_WIDTH;
}

void EnergyBar::onDraw(RenderTarget &target, const Transform &transform)
{
    target.draw(rectBorder);
    target.draw(rectEnergy);
}

