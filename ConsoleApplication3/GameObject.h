#pragma once

#include <string>
#include <iostream>
#include <random>
#include "sfml.h"
#include "Utils.h"

//GameObject: super-class for all in-game objects

//TODO
//Put ID into a std::map and do std-ish mappy things

class GameObject :
	public sf::Sprite
{
private:
	//int speed;
	std::string msg; //message dislayed when interacted with.

public:
	GameObject(); //cannot be represented without ID
	GameObject(float x, float y);
	//GameObject(sf::Texture _image);
	~GameObject(void);

	//Set/Get
	/*void setSpeed(float _speed) {
		speed = _speed;
	}
	float getSpeed()
	{
		return speed;
	}*/
	std::string getMsg()
	{
		return msg;
	}

	//sf::Texture image;
	virtual void update(float dt); //to be over-ridden

	void follow(GameObject other, float deltaTime = 0, float speed = 0);

	void setRotationCoord(float angle, float offX = 16.0f, float offY = 16.0f);
};

