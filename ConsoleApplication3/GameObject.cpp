#include "GameObject.h"

GameObject::GameObject() 
{
}

GameObject::GameObject(TextureManager& texMan)
{
	//preferred method, allows for loading textures in a better way
}

void GameObject::update(float dt)
{
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
