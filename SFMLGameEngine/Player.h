#pragma once
#include "GameObject.h"
#include "sfml.h"


class Player :
	public GameObject
{
public:
	//Player(void);
	Player(TextureManager& texMan);
	~Player(void);

	sf::Texture playerTexture; //so that it's only loaded once
	sf::Texture playerDTexture;

	GameObject myTestObject;

	using GameObject::update;
	virtual void update(float dt);
	using GameObject::updateCollision;
	virtual void updateCollision(float dt, std::vector<std::unique_ptr<GameObject>> &others);

	bool inAir = false;
	bool killed = false;
	sf::Clock killClock;
	float killTime = 3.0f;
	int hasJumped = 0;
	bool jumpPressed = false;
};

