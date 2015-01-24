#include  "../include/Player.hpp"

float Player::maxRunSpeed = 5000.0;
float Player::maxJumpSpeed = 800.0;
float Player::gravity = 2800.0;
float Player::friction = 10.0;
float Player::maxEnergy = 1000.0;
float Player::regenSpeed = 50.0;

Player::Player(Keyboard::Key j, Keyboard::Key l, Keyboard::Key r)
    : energy(maxEnergy), isPlayerOne(false), xSpeed(0), ySpeed(0), canJump(false), jumpKey(j), leftKey(l), rightKey(r)
{
    setPosition(0, 400);
}

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

    checkCollisions(dt);
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

void Player::checkCollisions(float dt)
{
    Level* l = (Level*) PeezyWin::peekScene();
    for (Block* block : l->blocks) {

        Rect<float> meRectObj = getGlobalBounds();
        Rect<float> bRectObj = block->getGlobalBounds();
        Rect<float> *meRect = &meRectObj;
        Rect<float> *bRect = &bRectObj;

        if (bRect->intersects(*meRect)) {

            float lastXSpeed = xSpeed*dt, lastYSpeed = ySpeed*dt;
            *meRect = Rect<float>(meRect->left, meRect->top - lastYSpeed, meRect->width, meRect->height);
            if (bRect->intersects(*meRect))
            {
                if (lastXSpeed > 0) {
                    setPosition(bRect->left - meRect->width, meRect->top);
                } else {
                    setPosition(bRect->left + bRect-> width, meRect->top);
                }
                xSpeed = 0.0f;
            }
            else {
                *meRect = Rect<float>(meRect->left - lastXSpeed, meRect->top + lastYSpeed, meRect->width, meRect->height);
                if (bRect->intersects(*meRect))
                {
                    if (ySpeed >= 0) hitFloor(bRect->top);
                    else if(ySpeed < 0) hitCeil(bRect->top + bRect->height);
                }
            }
        }
    }
}


void Player::onDraw(RenderTarget& target, const Transform& transform) {
  GameObject::onDraw(target, transform);
  sf::CircleShape shape(Level::maxDistance);
  shape.setFillColor(Color::Transparent);
  shape.setOutlineColor(Color::Blue);
  shape.setOutlineThickness(3);
  Transform circleTransform = getTransform() * transform;
  circleTransform.translate(-Level::maxDistance,-Level::maxDistance);
  circleTransform.translate(getGlobalBounds().width/2, getGlobalBounds().height/2);
  target.draw(shape, circleTransform);
}
