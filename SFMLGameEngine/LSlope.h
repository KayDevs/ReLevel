#pragma once
#include "GameObject.h"

class LSlope :
	public GameObject
{
public:
	//Block(void);
	LSlope(TextureManager& texMan);
	~LSlope(void);

	sf::Texture lslopeTexture;

	virtual void update(float dt);
};

