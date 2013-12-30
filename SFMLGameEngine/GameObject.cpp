#include "GameObject.h"

GameObject::GameObject() 
{
}

GameObject::GameObject(TextureManager& texMan)
{
	//preferred method, allows for loading textures in a better way
}

void GameObject::updateCollision(float dt, std::vector<std::unique_ptr<GameObject>> &others)
{

}

void GameObject::update(float dt)
{
	//hspeed += haccel * dt;
	//vspeed += vaccel * dt;
	vspeed += grav * dt;
	move(hspeed * dt, vspeed * dt);
	if (vspeed > 12.0f)
		vspeed = 12.0f;
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
