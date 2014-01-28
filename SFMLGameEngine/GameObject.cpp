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
	vspeed += grav;
	//move(hspeed * dt, vspeed * dt);
	move(hspeed, vspeed);
	if (vspeed > 12.0f)
		vspeed = 12.0f;
}
