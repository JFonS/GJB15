#include  "../include/Player.hpp"

float Player::maxRunSpeed = 5000.0;
float Player::maxJumpSpeed = 800.0;
float Player::gravity = 2800.0;
float Player::friction = 10.0;

Player::Player(Keyboard::Key j, Keyboard::Key l, Keyboard::Key r)
    :xSpeed(0), ySpeed(0), canJump(false), jumpKey(j), leftKey(l), rightKey(r) {}

void Player::onUpdate(float dt)
{
    move(xSpeed * dt, ySpeed * dt);

    ySpeed = ySpeed + (gravity * dt);
    xSpeed = xSpeed * (1 - min(dt * friction, 1.0f));

    if (Keyboard::isKeyPressed(leftKey)) {
        xSpeed -= maxRunSpeed * dt;
        xSpeed = min(xSpeed, maxRunSpeed);
    }

    if (Keyboard::isKeyPressed(rightKey)) {
        xSpeed += maxRunSpeed * dt;
        xSpeed = max(xSpeed, -maxRunSpeed);
    }

    checkCollisions();
}

void Player::onKeyDown(PEvent &e) {
    if (e.key.code == jumpKey) jump();
}

void Player::hitFloor(float height)
{
    setPosition(getPosition().x, height - getGlobalBounds().height);
    ySpeed = 0.0;
    canJump = true;
}

void Player::hitCeil(float height)
{
    setPosition(getPosition().x, height);
    ySpeed = 0.0;
}

void Player::jump()
{
    if (canJump) {
        ySpeed = -maxJumpSpeed;
        canJump = false;
    }
}

void Player::checkCollisions()
{
    Level* l = (Level*) PeezyWin::peekScene();
    for (Block* block : l->blocks) {
        Rect<float> meRect = getGlobalBounds();
        Rect<float> bRect = block->getGlobalBounds();
        if (block->getGlobalBounds().intersects(meRect)) {
            if (ySpeed > 0)
                hitFloor(bRect.top);
            else if(ySpeed < 0)
                hitCeil(bRect.top + bRect.height);
        }
    }
}
