#include "Block.h"


//Block::Block(void){}

Block::Block(TextureManager& texMan)
{
	blockTexture = texMan.getTexture("Block.png");
	setTexture(blockTexture);

	blockShape = new sf::RectangleShape();
	blockShape->setPosition(getPosition());
	blockShape->setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
}


Block::~Block(void)
{
}

void Block::update(float dt)
{
	//a block does literally nothing.
}
