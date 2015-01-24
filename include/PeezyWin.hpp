#ifndef PEEZYWIN_HPP
#define PEEZYWIN_HPP

#include "../include/Debug.hpp"
#include "../include/Scene.hpp"
#include "../include/Level.hpp"
#include "../include/MovieClip.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <stack>

using namespace std;
using namespace sf;

class Level;

typedef stack<Scene*> SceneStack;

class PeezyWin {
public:
  static Scene *mainMenu;
  static Level *level1;

  PeezyWin(Vector2i size);
  virtual ~PeezyWin();
  void play();

  static void pushScene(Scene* sc);
  static void popScene();
  static void changeScene(Scene* sc);
  static Scene* peekScene();
  static RenderWindow* window;

  static int winWidth, winHeight;
protected:
  void _loop();
   
  virtual void startUp();
  virtual void loop(float dt);
  

  static SceneStack scenes;
};

#endif
