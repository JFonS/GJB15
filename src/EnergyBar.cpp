#include "../include/EnergyBar.hpp"

EnergyBar::EnergyBar() : GameObject()
{
    shad = new Shader();
    shad->loadFromFile("assets/energyBarFrag", Shader::Fragment);

    Texture *t = new Texture();
    t->create(10, 10);
    rect.setTexture(t);
    shad->setParameter("tex", *t);
    rect = RectangleShape(Vector2f(BAR_WIDTH, BAR_HEIGHT));
    rect.setOrigin(Vector2f(BAR_WIDTH/2, BAR_HEIGHT/2));
    rect.setPosition(PeezyWin::winWidth / 2, 25.0f);
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
    rs.shader = shad;
    target.draw(rect, rs);
}

