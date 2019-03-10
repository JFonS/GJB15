#include  "../include/Player.hpp"

#include <cmath>

float Player::maxRunSpeed = 5000.0;
float Player::maxJumpSpeed = 800.0;
float Player::gravity = 2800.0;
float Player::friction = 10.0;
float Player::maxEnergy = 1000.0;
float Player::regenSpeed = 150.0;

Player::Player(Keyboard::Key j, Keyboard::Key l, Keyboard::Key r)
    : energy(maxEnergy), isPlayerOne(false), xSpeed(0), ySpeed(0), canJump(false), jumpKey(j), leftKey(l), rightKey(r)
{
    hitBox = new RectangleShape(Vector2f(50.0, 70.0));

    setPosition(100, 400);
    addKeyFrame(0, "runRight");
    addKeyFrame(7, "FrunRight");
    addKeyFrame(8, "runLeft");
    addKeyFrame(15, "FrunLeft");
    timePerFrame = 0.05f;
    lookingRight = true;
    shad = new Shader();
    shad->loadFromFile("assets/circleFrag", Shader::Fragment);
    levelCompleted = false;
    stop();
}

void Player::setHitbox() {
    hitXOffset = getLocalBounds().width/2 - hitBox->getLocalBounds().width/2;
    hitYOffset = getLocalBounds().height - hitBox->getLocalBounds().height;
}

void Player::onUpdate(float dt)
{
    move(xSpeed * dt, ySpeed * dt);
    updateHitbox();

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
    if(std::abs(xSpeed*dt) < 0.005f) xSpeed = 0.0f;

    if(xSpeed == 0.0f)
    {
        if(lookingRight) gotoAndStop("FrunRight");
        else gotoAndStop("runLeft");
    }
    else if(xSpeed < 0 && (lookingRight  || !playing)) { lookingRight = false; gotoAndPlay("runLeft"); }
    else if(xSpeed > 0 && (!lookingRight || !playing)) { lookingRight = true;  gotoAndPlay("runRight"); }
    updateHitbox();
}

void Player::onKeyDown(PEvent &e) {
    if (e.key.code == jumpKey) jump();
}

void Player::hitFloor(float height)
{
    setPosition(getPosition().x, height - getGlobalBounds().height);
    updateHitbox();
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

bool Player::hitting(const Block *b)
{
    Rect<float> pRect = hitBox->getGlobalBounds(); // Player rectangle
    pRect.height += 2.0f;
    Rect<float> oRect = b->getGlobalBounds();
    oRect.width = 15.0f;
    oRect.left += 27.5f;

    return pRect.intersects(oRect);
}

void Player::gotoPortal(const Block *destiny)
{
    setPosition(destiny->getPosition() - Vector2f(hitXOffset, getGlobalBounds().height + 3.0f));
    updateHitbox();
    if(std::abs(ySpeed) < maxJumpSpeed) ySpeed = maxJumpSpeed;
    ySpeed *= -1.1f;
}

void Player::onKeyUp(PEvent &e)
{

}

void Player::updateHitbox(){
    hitBox->setPosition(getPosition().x + hitXOffset, getPosition().y + hitYOffset);
}

void Player::checkCollisions(float dt)
{
    Level* l = (Level*) PeezyWin::peekScene();
    for (Block* block : l->blocks)
    {
        if(isDoor(block->GetType()) && !block->enabled)  continue;
        if(isPortal(block->GetType())) continue;
        if(block->GetType() == LIGHT) continue;

        Rect<float> pRect = hitBox->getGlobalBounds(); // Player rectangle
        Rect<float> oRect = block->getGlobalBounds(); //Rect<float>(block->getPosition().x, block->getPosition().y, block->getGlobalBounds().width, block->getGlobalBounds().height);

        if (pRect.intersects(oRect))
        {
            const float mult = 1.1f;
            //MOVEMENT HANDLE
            hitBox->move(0.0,-ySpeed * dt * mult);
            if (hitBox->getGlobalBounds().intersects(oRect)) {
                hitBox->move(0.0,ySpeed * dt * mult);
                //PROBLEMA EN LES X
                if (xSpeed > 0) {
                    setPosition(oRect.left - pRect.width - hitXOffset, getPosition().y);
                    updateHitbox();
                } else if(xSpeed < 0){
                    setPosition(oRect.left + oRect.width - hitXOffset, getPosition().y);
                    updateHitbox();
                }
            } else {
                hitBox->move(0.0,ySpeed * dt * mult);
                //PROBLEMA EN LES Y
                if(ySpeed > 0) {
                    hitFloor(block->getPosition().y);
                } else if(ySpeed < 0){
                    hitCeil(block->getPosition().y + block->getLocalBounds().height);
                }
                updateHitbox();
            }
        }
    }
}


void Player::onDraw(RenderTarget& target, const Transform& transform)
{
  Level *l = (Level*) PeezyWin::peekScene();
  sf::CircleShape shape(Level::maxDistance);
  Vector2f v = (l->player1->getPosition() - l->player2->getPosition());
  float alphaIndex = 0.3f;
  float minAlpha = 0.2f;

  if(isPlayerOne)
  {
      shape.setFillColor(Color(255, 25, 25, 50 * min(1.0f, alphaIndex + minAlpha)));
      shape.setOutlineColor(Color(200, 25, 25, 255 * min(1.0f, alphaIndex + minAlpha)));
  }
  else
  {
      shape.setFillColor(Color(25, 25, 255, 50 * min(1.0f, alphaIndex + minAlpha) ));
      shape.setOutlineColor(Color(25, 25, 200, 255 * min(1.0f, alphaIndex + minAlpha) ));
  }

  shape.setPointCount(100); //moar quality
  shape.setOutlineThickness(2);

  Transform circleTransform = getTransform() * transform;
  circleTransform.translate(-Level::maxDistance,-Level::maxDistance);
  circleTransform.translate(getGlobalBounds().width/2, getGlobalBounds().height/2);

  if(isPlayerOne)
  {
      shad->setParameter("blue", 0.0f);
  }
  else
  {
      shad->setParameter("blue", 1.0f);
  }

  shad->setParameter("rad", Level::maxDistance);
  Vector2f p2Center = Vector2f(l->player2->getGlobalBounds().left + l->player2->getGlobalBounds().width/2, PeezyWin::winHeight - (l->player2->getGlobalBounds().top + l->player2->getGlobalBounds().height/2));
  Vector2f p1Center = Vector2f(l->player1->getGlobalBounds().left + l->player1->getGlobalBounds().width/2, PeezyWin::winHeight - (l->player1->getGlobalBounds().top + l->player1->getGlobalBounds().height/2));
  shad->setParameter("pos1", l->camera.getInverse() * p1Center);
  shad->setParameter("pos2", l->camera.getInverse() * p2Center);
  RenderStates rs(shad);
  rs.transform = circleTransform;
  target.draw(shape, rs);

  GameObject::onDraw(target, transform);
}
