#include "../include/Scene.hpp"
#include "../include/Node.hpp"
#include "../include/Debug.hpp"

Scene::Scene(string n) {
  Node::name = n;
}

Scene::~Scene()
{
    DbgWarning("destroyed");
}

void Scene::onUpdate(float dt) {}

void Scene::onDraw(RenderTarget& target, const Transform& transform){
}

void Scene::draw(RenderTarget& target)
{
  Transform inverseCamera = camera.getInverse();
  childrenOrder.sort(zIndexSort);
  for (auto p : childrenOrder) p->draw(target, inverseCamera);
}

const Transform & Scene::getNodeTransform()
{
    return Transform::Identity;
}

Rect<float> Scene::getBoundingBox()
{
    return Rect<float>();
}

