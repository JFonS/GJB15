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
    hitBox = new RectangleShape(Vector2f(50.0,100.0));

    setPosition(100, 400);
    addKeyFrame(0, "runRight");
    addKeyFrame(7, "FrunRight");
    addKeyFrame(8, "runLeft");
    addKeyFrame(15, "FrunLeft");
    timePerFrame = 0.05f;
    lookingRight = true;
    stop();
}

void Player::setHitbox() {
    hitOffset = getLocalBounds().width/2 - hitBox->getLocalBounds().width/2;
}

void Player::onUpdate(float dt)
{
    move(xSpeed * dt, ySpeed * dt);
    hitBox->setPosition(getPosition().x + hitOffset,getPosition().y);
    //if (isPlayerOne) DbgLog(getPosition() << hitBox->getPosition());

    checkCollisions(dt);

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
    if(abs(xSpeed*dt) < 0.5f) xSpeed = 0.0f;

    if(xSpeed == 0.0f)
    {
        if(lookingRight) gotoAndStop("FrunRight");
        else gotoAndStop("runLeft");
    }
    else if(xSpeed < 0 && (lookingRight  || !playing)) { lookingRight = false; gotoAndPlay("runLeft"); }
    else if(xSpeed > 0 && (!lookingRight || !playing)) { lookingRight = true;  gotoAndPlay("runRight"); }
}

void Player::onKeyDown(PEvent &e) {
    if (e.key.code == jumpKey) jump();
}

void Player::hitFloor(float height)
{
    setPosition(getPosition().x, height - getGlobalBounds().height);
    hitBox->setPosition(getPosition().x + hitOffset, getPosition().y);
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

void Player::onKeyUp(PEvent &e)
{

}
void Player::updateHitbox(){
    hitBox->setPosition(getPosition().x + hitOffset, getPosition().y);
}

void Player::checkCollisions(float dt)
{
    Level* l = (Level*) PeezyWin::peekScene();
    for (Block* block : l->blocks)
    {
        Rect<float> pRect = hitBox->getGlobalBounds(); // Player rectangle
        Rect<float> oRect = block->getGlobalBounds(); //Rect<float>(block->getPosition().x, block->getPosition().y, block->getGlobalBounds().width, block->getGlobalBounds().height);

        if (pRect.intersects(oRect)) {
            hitBox->move(0.0,-ySpeed * dt);
            if (hitBox->getGlobalBounds().intersects(oRect)) {
                hitBox->move(0.0,ySpeed * dt);
                //PROBLEMA EN LES X
                if (xSpeed > 0) {
                    setPosition(oRect.left - pRect.width - hitOffset, getPosition().y);
                    updateHitbox();
                } else {
                    setPosition(oRect.left + oRect.width - hitOffset, getPosition().y);
                    updateHitbox();
                }
            } else {
                hitBox->move(0.0,ySpeed * dt);
                //PROBLEMA EN LES Y

                if(ySpeed > 0) {
                    hitFloor(block->getPosition().y);
                } else {
                    hitCeil(block->getPosition().y + block->getLocalBounds().height);
                }
                updateHitbox();
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
