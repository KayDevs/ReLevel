#pragma once
#include "GameObject.h"
#include "Collision.h"
#include "sfml.h"


class Player :
	public GameObject
{
public:
	Player(void);
	Player(float x, float y);
	~Player(void);

	sf::Texture playerTexture; //so that it's only loaded once
	sf::Texture playerDTexture;

	GameObject myTestObject;

	using GameObject::update;
	virtual void update(float dt);
};

