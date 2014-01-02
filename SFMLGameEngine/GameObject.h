#pragma once

#include <string>
#include <iostream>
#include <random>
#include "sfml.h"
#include "Utils.h"
#include "TextureManager.h"

//GameObject: super-class for all in-game objects
//not abstract; can be instantiated

class GameObject :
	public sf::Sprite
{
	public:
		GameObject(); 	
		GameObject(TextureManager& texMan);

		sf::ConvexShape collision;
		bool solid = false;
		bool kill = false;

		float hspeed = 0.0f, vspeed = 0.0f;
		float haccel = 0.0f, vaccel = 0.0f;
		float grav = 0.5f;

		virtual void updateCollision(float dt, std::vector<std::unique_ptr<GameObject>> &others);
		virtual void update(float dt); //to be over-ridden

};

