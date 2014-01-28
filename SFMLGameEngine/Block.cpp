#include "Block.h"


//Block::Block(void){}

Block::Block(TextureManager& texMan)
{
	blockTexture = texMan.getTexture("Block.png");
	setTexture(blockTexture);

	solid = true;
	collision.setPointCount(4);
	collision.setPosition(getPosition());
	collision.setPoint(0, sf::Vector2f(0, 0));
	collision.setPoint(1, sf::Vector2f(32, 0));
	collision.setPoint(2, sf::Vector2f(32, 32));
	collision.setPoint(3, sf::Vector2f(0, 32));
}


Block::~Block(void)
{
}

void Block::update(float dt)
{
	collision.setPosition(getPosition());
}
