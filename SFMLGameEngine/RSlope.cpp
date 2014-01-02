#include "RSlope.h"


RSlope::RSlope(TextureManager& texMan)
{
	rslopeTexture = texMan.getTexture("RSlope.png");
	setTexture(rslopeTexture);

	solid = true;
	collision.setPointCount(3);
	collision.setPosition(getPosition());
	//collision.setPoint(0, sf::Vector2f(0, 0));
	collision.setPoint(0, sf::Vector2f(32, 0));
	collision.setPoint(1, sf::Vector2f(32, 32));
	collision.setPoint(2, sf::Vector2f(0, 32));
}


RSlope::~RSlope(void)
{
}

void RSlope::update(float dt)
{
	collision.setPosition(getPosition());
	/*collision.setPoint(0, sf::Vector2f(getPosition().x, getPosition().y));
	collision.setPoint(1, sf::Vector2f(getPosition().x + 32, getPosition().y));
	collision.setPoint(2, sf::Vector2f(getPosition().x + 32, getPosition().y + 32));
	collision.setPoint(3, sf::Vector2f(getPosition().x, getPosition().y + 32));*/
	//a block does literally nothing.
}
