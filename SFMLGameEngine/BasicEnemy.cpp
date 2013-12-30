#include "BasicEnemy.h"


//BasicEnemy::BasicEnemy(void){}

BasicEnemy::BasicEnemy(TextureManager& texMan)
{
	basicEnemyTexture = texMan.getTexture("BasicEnemy.png");
	setTexture(basicEnemyTexture);
	hspeed = 4.0f;
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
				hspeed = 4.0f; 	
			if(coll.smallest.x < 0.0f)
				hspeed = -4.0f;
			//move(coll.smallest.x * coll.overlap, coll.smallest.y * coll.overlap);
		}
	}
}
void BasicEnemy::update(float dt)
{
	/*std::cout<<"Enemy update!"<<std::endl;
	std::cout<<"Enemy x: "<<getPosition().x<<" Enemy y: "<<getPosition().y<<std::endl;*/
	GameObject::update(dt);
	collision.setPosition(getPosition());
}
