#pragma once

#include "GameObject.h"
#include "Player.h"
#include "BasicEnemy.h"
#include <string>
class GameObjectFactory
{
	public:
		GameObjectFactory(void);
		~GameObjectFactory(void);
		static GameObject* create(std::string class_name);
		static GameObject* create(int class_name);

};

enum
{
	PLAYER,
	BASICENEMY 
};
