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
#define PORTAL_START 23
#define PORTAL_END 27
#define FINISH 28
#define LIGHT 29
#define isDoor(x) (x >= DOOR_START && x <= DOOR_END)
#define isButton(x) (x >= BUTTON_START && x <= BUTTON_END)
#define isPalanca(x) (x >= PALANCA_START && x <= PALANCA_END)
#define isPortal(x) (x >= PORTAL_START && x <= PORTAL_END)

class Block : public GameObject
{
private:
    int type;
    Vector2f noiseCoords;
    float noiseAlpha;

public:
    static Texture *noiseTex;
    static Shader *shad;
    bool enabled;

    Block(int type);
    virtual ~Block();

    int GetType();
    virtual void onUpdate(float dt);
    virtual void onDraw(RenderTarget& target, const Transform& transform);
    static int getObjectIndex(int n);
};

#endif // BLOCK_HPP
