#include "../include/EnergyBar.hpp"

EnergyBar::EnergyBar() : GameObject()
{
    border = RectangleShape(Vector2f(BAR_WIDTH + 2.0f, BAR_HEIGHT + 1.0f));
    border.setFillColor(Color::Transparent);
    border.setOutlineColor(Color::White);
    border.setOutlineThickness(2.0f);

    bg = RectangleShape(border.getSize());
    bg.setFillColor(Color::Black);
    bg.setOutlineColor(Color::Transparent);

    shad = new Shader();
    shad->loadFromFile("assets/energyBarFrag", Shader::Fragment);

    Texture *t = new Texture(); t->create(BAR_WIDTH, BAR_HEIGHT);
    shad->setParameter("tex", Shader::CurrentTexture);
    rect = Sprite(*t);
    rect.setTextureRect(IntRect(0, 0, BAR_WIDTH, BAR_HEIGHT));
    rect.setOrigin(Vector2f(BAR_WIDTH/2, BAR_HEIGHT/2));
    rect.setPosition(PeezyWin::winWidth / 2, 25.0f);

    border.setOrigin(Vector2f(BAR_WIDTH/2 + 0.5f, BAR_HEIGHT/2 + 0.5f));
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

