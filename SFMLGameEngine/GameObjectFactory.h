#pragma once

#include "GameObject.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "Block.h"
#include "LSlope.h"
#include "RSlope.h"
#include <string>
class GameObjectFactory
{
	public:
		GameObjectFactory(void);
		~GameObjectFactory(void);
		static GameObject* create(std::string class_name);
		static GameObject* create(int class_name);
		static GameObject* create(std::string class_name, TextureManager& texMan);
		static GameObject* create(int class_name, TextureManager& texMan);

};

enum
{
	PLAYER,
	BASICENEMY,
	BLOCK,
	LSLOPE,
	RSLOPE
};
