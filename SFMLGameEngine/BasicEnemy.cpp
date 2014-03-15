#include "BasicEnemy.h"


//BasicEnemy::BasicEnemy(void){}

BasicEnemy::BasicEnemy(TextureManager& texMan)
{
	basicEnemyTexture = texMan.getTexture("BasicEnemy.png");
	setTexture(basicEnemyTexture);
	hspeed = -4.0f;
	collision.setPointCount(4);
	collision.setPosition(getPosition());
	collision.setPoint(0, sf::Vector2f(0, 0));
	collision.setPoint(1, sf::Vector2f(32, 0));
	collision.setPoint(2, sf::Vector2f(32, 32));
	collision.setPoint(3, sf::Vector2f(0, 32));
	grav = 0.0f;
	kill = true;
}


BasicEnemy::~BasicEnemy(void)
{
}

void BasicEnemy::updateCollision(float dt, std::vector<std::unique_ptr<GameObject>> &others)
{
	for(int i = 0; i < (int)others.size(); ++i)
	{
		GameObject* other = &(*others[i]); //get address of unique_ptr ... even though it's already a pointer??
		if(other->solid)
		{
			Utils::MTV coll = Utils::getCollision(collision, other->collision);
			if(coll.smallest.x > 0.0f)
			{
				//std::cout<<"Collision on left."<<std::endl;
				hspeed = 4.0f;
			}
			if(coll.smallest.x < 0.0f)
			{
				//std::cout<<"Collision on right."<<std::endl;
				hspeed = -4.0f;
			}
			//move(coll.smallest.x * coll.overlap, coll.smallest.y * coll.overlap);
		}
	}
}
void BasicEnemy::update(float dt)
{
	GameObject::update(dt);
	//std::cout<<"Enemy X coord: "<<getPosition().x<<std::endl;
	collision.setPosition(getPosition());
}
