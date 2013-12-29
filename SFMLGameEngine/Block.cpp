#include "Block.h"


//Block::Block(void){}

Block::Block(TextureManager& texMan)
{
	blockTexture = texMan.getTexture("Block.png");
	setTexture(blockTexture);

	solid = true;
	collision.setPointCount(4);
	collision.setPoint(0, sf::Vector2f(getPosition().x, getPosition().y));
	collision.setPoint(1, sf::Vector2f(getPosition().x + 32, getPosition().y));
	collision.setPoint(2, sf::Vector2f(getPosition().x + 32, getPosition().y + 32));
	collision.setPoint(3, sf::Vector2f(getPosition().x, getPosition().y + 32));
}


Block::~Block(void)
{
}

void Block::update(float dt)
{
	collision.setPoint(0, sf::Vector2f(getPosition().x, getPosition().y));
	collision.setPoint(1, sf::Vector2f(getPosition().x + 32, getPosition().y));
	collision.setPoint(2, sf::Vector2f(getPosition().x + 32, getPosition().y + 32));
	collision.setPoint(3, sf::Vector2f(getPosition().x, getPosition().y + 32));
	//a block does literally nothing.
}
