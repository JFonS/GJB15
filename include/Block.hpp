#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Level.hpp"
#include "ResourceManager.hpp"
#include "MovieClip.hpp"
#include "PEvent.hpp"
#include "Debug.hpp"

#define SOLID 1
#define BUTTON_START 17
#define BUTTON_END 21
#define DEATH 22
#define PALANCA_START 2
#define PALANCA_END 11
#define DOOR_START 12
#define DOOR_END 16
#define isDoor(x) (x >= DOOR_START && x <= DOOR_END)
#define isButton(x) (x >= DOOR_START && x <= DOOR_END)
#define isPalanca(x) (x >= DOOR_START && x <= DOOR_END)


class Block : public GameObject
{
private:
    int type;

public:
    bool enabled;

    Block(int type);
    virtual ~Block();

    int GetType();
    virtual void onUpdate(float dt);
    virtual void onDraw(RenderTarget& target, const Transform& transform);
    static int getObjectIndex(int n);
};

#endif // BLOCK_HPP
