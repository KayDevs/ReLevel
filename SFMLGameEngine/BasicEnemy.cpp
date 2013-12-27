#include "BasicEnemy.h"


//BasicEnemy::BasicEnemy(void){}

BasicEnemy::BasicEnemy(TextureManager& texMan)
{
	basicEnemyTexture = texMan.getTexture("BasicEnemy.png");
	setTexture(basicEnemyTexture);
}


BasicEnemy::~BasicEnemy(void)
{
}

void BasicEnemy::update(float dt)
{
	float speed = 4.0f;
	int direction = Utils::choose(4);
	switch(direction)
	{
	case 1:
		move(speed * dt, 0.0f);
		break;
	case 2:
		move(-speed * dt, 0.0f);
		break;
	case 3:
		move(0.0f, speed * dt);
		break;
	case 4:
		move(0.0f, -speed * dt);
		break;
	}
}
