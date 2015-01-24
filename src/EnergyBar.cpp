#include "../include/EnergyBar.hpp"

EnergyBar::EnergyBar(Player *p) : GameObject()
{
    attachedPlayer = p;
    rectBorder = RectangleShape(Vector2f(BAR_WIDTH, BAR_HEIGHT));
    rectBorder.setFillColor(Color::Transparent);
    rectBorder.setOutlineThickness(BAR_BORDER_THICKNESS);
    rectBorder.setOutlineColor(Color::White);
    rectEnergy = RectangleShape(Vector2f(BAR_WIDTH, BAR_HEIGHT));
    rectEnergy.setFillColor(Color::Green);

    rectBorder.setPosition(BAR_WIDTH - 50.0f, attachedPlayer->isPlayerOne ? 50.0f : 400.0f);
    rectEnergy.setPosition(BAR_WIDTH - 50.0f, (attachedPlayer->isPlayerOne ? 50.0f : 400.0f));
}

void EnergyBar::onUpdate(float dt)
{
    rectEnergy.setScale(max(0.0f, (attachedPlayer->energy / attachedPlayer->maxEnergy)), 1.0f);
}

void EnergyBar::onDraw(RenderTarget &target, const Transform &transform)
{
    target.draw(rectBorder);
    target.draw(rectEnergy);
}

