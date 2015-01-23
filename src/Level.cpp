#include "../include/Level.hpp"

float Level::cameraSpeed = 25.0;

Level::Level(string levelName) : Scene(levelName)
{
    name = levelName;
    DbgLog("created");
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
            Block *block = new Block();
            block->Sprite::setTexture(tileTextures[tiles[i]-1]);
            blocks.push_back(block);
            addChild(block);

            block->setPosition(currentx, currenty);
        }
        currentx += TILE_WIDTH;
        if(currentx >= LEVEL_WIDTH) { currenty += TILE_HEIGHT; currentx = 0; }
    }
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

    DbgLog("FINISHED READING FILE");
}

void Level::onUpdate(float dt) {
    camera.translate(dt*cameraSpeed, 0.0);
}
