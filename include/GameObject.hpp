#ifndef GAMEOBJECT_HPP
#define	GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "Debug.hpp"
#include "Node.hpp"
#include <string>
#include <map>
#include <list>

using namespace sf;
using namespace std;

class GameObject : public Sprite, public Node {
public:
    GameObject();
    GameObject(string name);
    GameObject(const GameObject& orig);
    virtual ~GameObject();

    void setTexture(string texture);
    virtual void onUpdate(float dt);

private:

    void onKeyDown(PEvent &e);
    void onMouseEnter(PEvent &e);
    void onMouseExit(PEvent &e);
    void onMouseOver();

    string textureName;
    const Transform & getNodeTransform();
protected:
    Rect<float> getBoundingBox();
    virtual void onDraw(RenderTarget& target, const Transform& transform);
};

#endif	/* GAMEOBJECT_HPP */
