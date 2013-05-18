#include "GameObjectFactory.h"


GameObjectFactory::GameObjectFactory(void)
{
}


GameObjectFactory::~GameObjectFactory(void)
{
}

//WARNING: IT IS NOT THE FACTORY'S RESPONSIBILITY TO HANDLE MEMORY

GameObject* GameObjectFactory::create(std::string class_name)
{
	if(class_name == "Player")
	{
		std::cout<<"Created: Player"<<std::endl;
		return (GameObject*)(new Player());
	}
	if(class_name == "BasicEnemy")
	{
		std::cout<<"Created: BasicEnemy"<<std::endl;
		return (GameObject*)(new BasicEnemy());
	}
	else
	{
		std::cout<<"Jive-ass data all up in this factory: "<< class_name << std::endl;
		return NULL;
	}
}



GameObject* GameObjectFactory::create(int class_name)
{
	if(class_name == PLAYER)
	{
		std::cout<<"Created: Player"<<std::endl;
		return (GameObject*)(new Player());
	}
	if(class_name == BASICENEMY)
	{
		std::cout<<"Created: BasicEnemy"<<std::endl;
		return (GameObject*)(new BasicEnemy());
	}
	else
	{
		std::cout<<"Jive-ass data all up in this factory: "<< class_name << std::endl;
		return NULL;
	}
}
