#pragma once
#include "GameObject.h"

class BasicEnemy :
	public GameObject
{
public:
	//BasicEnemy(void);
	BasicEnemy(TextureManager& texMan);
	~BasicEnemy(void);

	sf::Texture basicEnemyTexture;

	using GameObject::update;
	virtual void update(float dt);
	using GameObject::updateCollision;
	virtual void updateCollision(float dt, std::vector<std::unique_ptr<GameObject>> &others);
};

