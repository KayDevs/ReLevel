#pragma once
#include "GameObject.h"

class RSlope :
	public GameObject
{
public:
	RSlope(TextureManager& texMan);
	~RSlope(void);

	sf::Texture rslopeTexture;

	virtual void update(float dt);
};

