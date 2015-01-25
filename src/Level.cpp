#include "../include/Level.hpp"

float Level::c = 0.0f;
float Level::maxDistance = 200.0;

Level::Level(int levelNum) : Scene("level")
{
    cameraSpeed = 60.0;

    name = "level" + to_string(levelNum);
    string levelPath = "assets/level" + to_string(levelNum) + ".tmx";
    DbgLog(levelPath);
    loadFromFile("assets/newtileset.png", levelPath);

    Image img = Image();
    img.loadFromFile("assets/newtileset.png");

    Rect<int> tileImgFrame(0, 0, TILE_WIDTH, TILE_HEIGHT);
    tileTextures = new Texture[NUM_OF_DIF_TILES];
    for(int i = 0; i < NUM_OF_DIF_TILES; ++i)
    {
        tileTextures[i].loadFromImage(img, tileImgFrame);
        tileImgFrame = Rect<int>(tileImgFrame.left + TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT);
    }

    float currentx = 0, currenty = 0;
    for(int i = 0; i < int(tiles.size()); ++i)
    {
        if(tiles[i] > 0)
        {
            Block *block = new Block(tiles[i]);
            block->Sprite::setTexture(tileTextures[tiles[i]-1]);
            blocks.push_back(block);
            addChild(block);

            block->setPosition(currentx, currenty);
        }
        currentx += TILE_WIDTH;
        if(currentx >= LEVEL_WIDTH) { currenty += TILE_HEIGHT; currentx = 0; }
    }

    player1 =  new Player(Keyboard::Up, Keyboard::Left, Keyboard::Right);
    player1->loadSpriteSheet("assets/pluslyreduced.png", 16);
    player1->isPlayerOne = true;
    player1->setHitbox();
    player1->setIndex(100);
    addChild(player1);

    player2 =  new Player(Keyboard::W,Keyboard::A,Keyboard::D);
    player2->loadSpriteSheet("assets/lesslyreduced.png", 16);
    player2->setHitbox();
    player2->setIndex(100);
    addChild(player2);

    EnergyBar *b1 = new EnergyBar(player1), *b2 = new EnergyBar(player2);
    addChild(b1); addChild(b2);

    player1->setIndex(90); player2->setIndex(90);
    player1->setPosition(100.0f, 100.0f);
    b1->setIndex(200); b2->setIndex(200);

    GameObject *bg = new GameObject("bg");
    Texture *bgTex = new Texture();
    bgTex->create(LEVEL_WIDTH, LEVEL_HEIGHT);
    bgTex->loadFromFile("assets/bg.png");
    bgTex->setRepeated(true);
    bg->setIndex(-1);
    addChild(bg);

    bg->Sprite::setTexture(*bgTex);
    bg->Sprite::setTextureRect(IntRect(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT));
}

Level::~Level()
{
    for(int i = 0; i < int(blocks.size()); ++i) delete blocks[i];
    delete[] tileTextures;
}

void Level::Reset()
{
    Level *l = new Level(PeezyWin::currentLevel);
    PeezyWin::changeScene(l);
}

void Level::Complete()
{
    if(!PeezyWin::goToNextLevel()) Reset();
}

void Level::loadFromFile(string tilesetFile, string tileMapFile)
{
    string line;
    ifstream file(tileMapFile);
    while(getline(file, line))
    {
        istringstream iss(line);
        char firstChar = line[0];
        if(firstChar != ' ' and firstChar != '<')
        {
            int nextTile; char c;
            while(iss >> nextTile) { tiles.push_back(nextTile); iss >> c;}
        }
        else if(firstChar == ' ' || firstChar == '<')
        {
            int inicio = line.find("cameraSpeed\"");
            if(inicio > 0)
            {
                inicio += strlen("cameraSpeed\"");
                inicio = line.find("value", inicio + 1) + strlen("value=\"");
                int final = line.find('"', inicio+1);
                string camSpeedString = line.substr(inicio, final - inicio);
                DbgLog("===" << camSpeedString << "===");
                cameraSpeed = atoi(camSpeedString.c_str());
            }
        }
    }

    for(int i = 0; i < int(tiles.size()); ++i)
    {
        cout << tiles[i] << ",";
    }
}

void Level::onKeyDown(PEvent &e)
{
    if(e.key.code == Keyboard::R)
    {
        Reset();
    }
    else if(e.key.code == Keyboard::P)
    {
        if(!PeezyWin::goToNextLevel()) Reset();
    }
    else if(e.key.code == Keyboard::O)
    {
        if(!PeezyWin::goToPreviousLevel()) Reset();
    }

}

void Level::onUpdate(float dt)
{
    player1->levelCompleted = player2->levelCompleted = false;

    c += dt;
    camera.translate(dt*cameraSpeed, 0.0);

    bool bad1, bad2;
    bad1 = bad2 = false;

    float xd = player1->getPosition().x - player2->getPosition().x;
    float yd = player1->getPosition().y - player2->getPosition().y;

    if (sqrt(xd * xd + yd * yd) > 2 * maxDistance) bad1 = bad2 = true;

    if (camera.getInverse().transformPoint(player1->getPosition()).x + player1->getGlobalBounds().width/2 < 0.0) {
        bad1 = true;
    }

    if (camera.getInverse().transformPoint(player2->getPosition()).x + player2->getGlobalBounds().width/2 < 0.0) {
        bad2 = true;
    }

    if (bad1) {
        player1->energy -= Player::regenSpeed; if(player1->energy < 0.0f) player1->energy = 0.0f;
    } else {
         player1->energy = min(player1->energy + Player::regenSpeed, Player::maxEnergy);
    }

    if (bad2) {
        player2->energy -= Player::regenSpeed; if(player2->energy < 0.0f) player2->energy = 0.0f;
    } else {
        player2->energy = min(player2->energy + Player::regenSpeed, Player::maxEnergy);
    }

    if(player1->energy <= 0.0f || player2->energy <= 0.0f)
    {
        Reset();
    }

}
