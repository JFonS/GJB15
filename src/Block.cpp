#include "../include/Block.hpp"

Block::Block(int type)
{
    this->type = type;
}

Block::~Block()
{
}

void Block::onUpdate(float dt)
{
}


int Block::GetType()
{
    return type;
}
