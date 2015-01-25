#include "../include/PeezyWin.hpp"

MainMenu *PeezyWin::mainMenu = nullptr;
Music PeezyWin::menuMusic, PeezyWin::gameMusic;

Intro *PeezyWin::intro = nullptr;
SceneStack PeezyWin::scenes = SceneStack();
RenderWindow* PeezyWin::window = nullptr;
int PeezyWin::currentLevel = 1;

int PeezyWin::winHeight = 700, PeezyWin::winWidth = 1200;

void PeezyWin::exit()
{
    window->close();
}

PeezyWin::PeezyWin(Vector2i size)
{
    window = new RenderWindow(VideoMode(size.x, size.y), "", Style::Titlebar | Style::Close);
    menuMusic.openFromFile("assets/music/menu.wav");
    gameMusic.openFromFile("assets/music/game.wav");
    menuMusic.setVolume(30);
    startUp();
}

PeezyWin::~PeezyWin()
{
    while(!scenes.empty())
    {
        delete scenes.top();
        scenes.pop();
    }
}

bool PeezyWin::goToFirstLevel()
{
    currentLevel = 0;
    return goToNextLevel();
}

bool PeezyWin::goToNextLevel()
{
    ++currentLevel;
    if(currentLevel <= NUM_LEVELS)
    {
        Level *l = new Level(currentLevel);
        PeezyWin::changeScene(l);
        return true;
    } else --currentLevel;
    return false;
}

bool PeezyWin::goToPreviousLevel()
{
    --currentLevel;
    if(currentLevel >= 1)
    {
        Level *l = new Level(currentLevel);
        PeezyWin::changeScene(l);
        return true;
    } else ++currentLevel;
    return false;
}

void PeezyWin::pushScene(Scene* sc)
{
  scenes.push(sc);
}

void PeezyWin::popScene() {
  scenes.pop();
}

void PeezyWin::changeScene(Scene* sc){
  if(scenes.empty()) popScene();
  pushScene(sc);
  return;
}

Scene* PeezyWin::peekScene(){
  if(scenes.empty()) return nullptr;
  return scenes.top();
}

void PeezyWin::startUp()
{
    mainMenu = new MainMenu();
    this->pushScene(mainMenu);

    intro = new Intro();
}

void PeezyWin::loop(float dt)
{

}

void PeezyWin::_loop() {
    Clock deltaClock;
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
            {
                window->close();
                return;
            }
            else if (peekScene() != NULL)
            {
              PEvent e(event);
              if(e.type == e.EventType::KeyPressed)
              {
                  if(e.key.code == Keyboard::Escape)
                    window->close();
              }
              peekScene()->onEvent(e);
            }
        }
        window->clear();
        Time dTime = deltaClock.restart();
        float dt = dTime.asSeconds();
        loop(dt);
        if (peekScene() != NULL) {
          peekScene()->update(dt);
          peekScene()->draw(*window);
        }
        window->display();
    }
}

void PeezyWin::play() {
    startUp();
    _loop();
}
