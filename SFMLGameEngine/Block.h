#pragma once
#include "GameObject.h"

class Block :
	public GameObject
{
public:
	//Block(void);
	Block(TextureManager& texMan);
	~Block(void);

	sf::Texture blockTexture;

	using GameObject::update;
	virtual void update(float dt);
};

