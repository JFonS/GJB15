#include "../include/PeezyWin.hpp"
#include "../include/Debug.hpp"
#include "../include/GameObject.hpp"
#include "../include/PText.hpp"
#include "../include/ButtonText.hpp"
#include "../include/Player.hpp"

Scene *PeezyWin::mainMenu = nullptr;
Level *PeezyWin::level1 = nullptr;
Intro *PeezyWin::intro = nullptr;
SceneStack PeezyWin::scenes = SceneStack();
RenderWindow* PeezyWin::window = nullptr;

int PeezyWin::winHeight = 700, PeezyWin::winWidth = 1200;

PeezyWin::PeezyWin(Vector2i size)
{
    window = new RenderWindow(VideoMode(size.x, size.y), "", Style::Titlebar | Style::Close);
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

void PeezyWin::pushScene(Scene* sc)
{
  DbgLog("Pushed scene: " << sc->getName());
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
    mainMenu = new Scene("mainMenu");
    GameObject *menuBG = new GameObject("menuBG");
    menuBG->setTexture("assets/menu.png");
    ButtonText *playButton = new ButtonText();
    playButton->setString("PLAY");
    float w = playButton->getGlobalBounds().width;
    playButton->setPosition(PeezyWin::winWidth/2-w/2, PeezyWin::winHeight/2);
    playButton->downFunction = [](){PeezyWin::changeScene(PeezyWin::intro);};
    mainMenu->addChild(playButton);
    mainMenu->addChild(menuBG);
    menuBG->setIndex(-1);
    this->pushScene(mainMenu);

    level1 = new Level("level2");

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
            if (event.type == Event::Closed) {
                window->close();DbgLog("closed");
                return;
            }
            else if (peekScene() != NULL) {
              PEvent e(event);
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
