#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../include/MovieClip.hpp"
#include "../include/Debug.hpp"
#include "../include/PeezyWin.hpp"

class Level;

class Player : public MovieClip {
public:
    Player(Keyboard::Key j, Keyboard::Key l, Keyboard::Key r);
    void  onUpdate(float dt) override;

private:

    void onDraw(RenderTarget& target, const Transform& transform);

    float xSpeed, ySpeed;
    bool canJump;

    void hitFloor(float height);
    void hitCeil(float height);
    void jump();

    void onKeyDown(PEvent &e);
    void checkCollisions(float dt);

    static float maxRunSpeed, maxJumpSpeed, gravity, friction;
    Keyboard::Key jumpKey, leftKey, rightKey;
};

#endif // PLAYER_HPP
