#pragma once

#include <string>
#include <iostream>
#include <random>
#include "sfml.h"
#include "Utils.h"
#include "TextureManager.h"

//GameObject: super-class for all in-game objects

class GameObject :
	public sf::Sprite
{
	private:
		const std::string msg; //message dislayed when interacted with.

	public:
		GameObject(); 	
		GameObject(TextureManager& texMan);

		std::string getMsg()
		{
			return msg;
		}

		//sf::Texture image;
		virtual void update(float dt); //to be over-ridden

		void follow(GameObject other, float deltaTime = 0, float speed = 0);

		//	void setRotationCoord(float angle, float offX = 16.0f, float offY = 16.0f);
};

