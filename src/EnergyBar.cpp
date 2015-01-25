#include "../include/EnergyBar.hpp"

EnergyBar::EnergyBar() : GameObject()
{
    Texture *tRect   = new Texture; tRect->loadFromFile("assets/");
    Texture *tBorder = new Texture; tRect->loadFromFile("assets/");
    Texture *tBG     = new Texture; tRect->loadFromFile("assets/");

    rect = Sprite(*tRect);
    border = Sprite(*tBorder);
    bg = Sprite(*tBG);

    shad = new Shader();
    shad->loadFromFile("assets/energyBarFrag", Shader::Fragment);

    rect.setOrigin();
    rect.setPosition(PeezyWin::winWidth / 2, 25.0f);

    border.setPosition(rect.getPosition());
    bg.setOrigin(border.getOrigin());
    bg.setPosition(border.getPosition());
}

void EnergyBar::onUpdate(float dt)
{
    Level *l = (Level*) PeezyWin::peekScene();
    Player *p1 = l->player1, *p2 = l->player2;
    float minimumEnergy = min(p1->energy, p2->energy);
    rect.setScale(max(0.0f, (minimumEnergy / Player::maxEnergy)), 1.0f);
}

void EnergyBar::onDraw(RenderTarget &target, const Transform &transform)
{
    //target.draw(bg);
    RenderStates rs;
    rs.shader = shad;
    target.draw(rect, rs);
    target.draw(border);
}

