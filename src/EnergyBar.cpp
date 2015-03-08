#include "../include/EnergyBar.hpp"

EnergyBar::EnergyBar() : GameObject()
{
    Texture *tBorder = new Texture(); tBorder->loadFromFile("assets/pilaoutline.png");
    Texture *tRect   = new Texture(); tRect->loadFromFile("assets/pilagreen.png");
    Texture *tBG     = new Texture(); tBG->loadFromFile("assets/pilabuida");

    border = Sprite(*tBorder);
    rect = Sprite(*tRect);
    bg = Sprite(*tBG);

    //shad = new Shader();
    //shad->loadFromFile("assets/energyBarFrag", Shader::Fragment);

    rect.setPosition(PeezyWin::winWidth / 2 - tRect->getSize().x / 2, 25.0f);
    border.setPosition(rect.getPosition());
    bg.setPosition(rect.getPosition());
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
    RenderStates rs;
    //rs.shader = shad;
    target.draw(bg);
    target.draw(rect);
    target.draw(border);
}

