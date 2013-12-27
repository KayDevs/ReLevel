#include "Block.h"


//Block::Block(void){}

Block::Block(TextureManager& texMan)
{
	blockTexture = texMan.getTexture("Block.png");
	setTexture(blockTexture);
}


Block::~Block(void)
{
}

void Block::update(float dt)
{
	//a block does literally nothing.
}
