#include "../include/Level.hpp"

float Level::cameraSpeed = 25.0;
float Level::maxDistance = 200.0;

Level::Level(string levelName) : Scene(levelName)
{
    name = levelName;
    loadFromFile("assets/tileset.png", "assets/testTileMap.tmx");

    Image img = Image();
    img.loadFromFile("assets/tileset.png");

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

    player1 =  new Player(Keyboard::Up,Keyboard::Left,Keyboard::Right);
    player1->loadSpriteSheet("assets/pluslyreduced.png", 16);
    player1->isPlayerOne = true;
    //player1->hitBox = Rect<float>(player1->getGlobalBounds().width/2 - 25.0f, 0.0f, 50.0f, 100.0f);
    addChild(player1);

    player2 =  new Player(Keyboard::W,Keyboard::A,Keyboard::D);
    player2->loadSpriteSheet("assets/lesslyreduced.png", 16);
    //player2->hitBox = Rect<float>(player2->getGlobalBounds().width/2 - 25.0f, 0.0f, 50.0f, 100.0f);
    addChild(player2);

    EnergyBar *b1 = new EnergyBar(player1), *b2 = new EnergyBar(player2);
    addChild(b1); addChild(b2);

    player1->setIndex(90); player2->setIndex(90);
    b1->setIndex(200); b2->setIndex(200);
}

Level::~Level()
{
    for(int i = 0; i < int(blocks.size()); ++i) delete blocks[i];
    delete[] tileTextures;
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
    }

    for(int i = 0; i < int(tiles.size()); ++i)
    {
        cout << tiles[i] << ",";
    }
}

void Level::onUpdate(float dt)
{
    camera.translate(dt*cameraSpeed, 0.0);
    float xd = player1->getPosition().x - player2->getPosition().x;
    float yd = player1->getPosition().y - player2->getPosition().y;
    if (sqrt(xd * xd + yd * yd) > 2 * maxDistance)
    {
        player1->energy -= Player::regenSpeed; if(player1->energy < 0.0f) player1->energy = 0.0f;
        player2->energy -= Player::regenSpeed; if(player2->energy < 0.0f) player2->energy = 0.0f;
        ////// MIRAR SI ES MOR ALGU
    } else
    {
        player1->energy = min(player1->energy + Player::regenSpeed, Player::maxEnergy);
        player2->energy = min(player2->energy + Player::regenSpeed, Player::maxEnergy);
    }
}
