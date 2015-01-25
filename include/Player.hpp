#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../include/MovieClip.hpp"
#include "../include/Debug.hpp"
#include "../include/Block.hpp"
#include "../include/PeezyWin.hpp"

class Level;
class Block;

class Player : public MovieClip {
public:
    Player(Keyboard::Key j, Keyboard::Key l, Keyboard::Key r);
    void  onUpdate(float dt) override;
    float energy;
    static float maxEnergy, regenSpeed;
    bool isPlayerOne, lookingRight;
    bool levelCompleted;
    RectangleShape* hitBox;
    float hitXOffset, hitYOffset;
    void setHitbox();
    bool hitting(const Block *b);
    void gotoPortal(const Block *destiny);
    Shader *shad;

private:

    void updateHitbox();

    void onDraw(RenderTarget& target, const Transform& transform);

    float xSpeed, ySpeed;
    bool canJump;

    void hitFloor(float height);
    void hitCeil(float height);
    void jump();

    void onKeyUp(PEvent &e);
    void onKeyDown(PEvent &e);
    void checkCollisions(float dt);

    static float maxRunSpeed, maxJumpSpeed, gravity, friction;
    Keyboard::Key jumpKey, leftKey, rightKey;
};

#endif // PLAYER_HPP
