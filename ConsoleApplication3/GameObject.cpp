#include "GameObject.h"

//IMPLEMENT 'NAME' SYSTEM IN PLACE OF HARDCODED ID SYSTEM

GameObject::GameObject() 
{
	//speed = 0;
}

GameObject::GameObject(float x, float y)
{
	setPosition(x, y);
}

GameObject::~GameObject(void)
{
}

void GameObject::update(float dt)
{
	//setPosition(getPosition().x, getPosition().y + speed * deltaTime);
	//move(speed * dt, 0);
	//std::cout << "OBJECT CALLBACK " << ID << std::endl;
	//return EXIT_SUCCESS;
}

void GameObject::follow(GameObject other, float deltaTime, float speed)
{	
	setPosition(other.getPosition());
}

/*void GameObject::setRotationCoord(float angle, float offX, float offY)
{
	setOrigin(offX, offY);
	setRotation(angle);
	setOrigin(0.0f, 0.0f);
}*/