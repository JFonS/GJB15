#ifndef PEEZYWIN_HPP
#define PEEZYWIN_HPP

#include "../include/Debug.hpp"
#include "../include/Scene.hpp"
#include "../include/Level.hpp"
#include "../include/MainMenu.hpp"
#include "../include/MovieClip.hpp"
#include "../include/Intro.hpp"
#include "../include/GameObject.hpp"
#include "../include/PText.hpp"
#include "../include/ButtonText.hpp"
#include "../include/Player.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <stack>

using namespace std;
using namespace sf;

#define NUM_LEVELS 4

class Level;
class Intro;
class MainMenu;

typedef stack<Scene*> SceneStack;

class PeezyWin {
public:
  static Intro *intro;
  static MainMenu *mainMenu;
  static void exit();
  static int currentLevel;

  PeezyWin(Vector2i size);
  virtual ~PeezyWin();
  void play();

  static void pushScene(Scene* sc);
  static void popScene();
  static void changeScene(Scene* sc);
  static Scene* peekScene();
  static RenderWindow* window;

  static int winWidth, winHeight;

  static bool goToNextLevel();
  static bool goToPreviousLevel();
  static bool goToFirstLevel();
protected:
  void _loop();
   
  virtual void startUp();
  virtual void loop(float dt);

  static SceneStack scenes;
};

#endif
