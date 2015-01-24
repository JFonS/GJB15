#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "EnergyBar.hpp"
#include <string>
#include <iostream>
#include <fstream>

#define TILE_WIDTH 50
#define TILE_HEIGHT 50
#define LEVEL_WIDTH 50 * TILE_WIDTH
#define LEVEL_HEIGHT 14 * TILE_HEIGHT
#define NUM_OF_DIF_TILES 3

class Block;

using namespace std;

class Player;

class Level : public Scene
{
private:

    void loadFromFile(string tilesetFile, string tileMapFile);
    Texture *tileTextures;
    string name;
    vector<int> tiles;
    static float cameraSpeed;

    void onUpdate(float dt);

    Player *player1, *player2;

public:
    static bool buttonPressed;
    static float maxDistance;

    vector<Block*> blocks;


    Level(string levelName);
    ~Level();
};

#endif // LEVEL_HPP
