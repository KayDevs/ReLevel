#include "Utils.h"
#include <iostream>
#include <vector>

//Utils::function = ;

int Utils::choose(int n)
{
	//list of axes are the polygon's normals 
	//normals obtained by flipping coordinates and negating one, then normalizing
	//i.e. (x, y) -> (-y, x) or (y, -x)
	//projections obtained by finding min. and max. vertex in polygon relative to axis
	//loop over axes to obtain whether or not projections overlap, if they don't, no collision exit immediately
	return (rand() % (n - 1)) + 1;
}

bool Utils::isColliding(sf::ConvexShape a, sf::ConvexShape b)
{
	if(Utils::getCollision(a, b).overlap == -1)
		return false;
	return true;
}

Utils::MTV Utils::getCollision(sf::ConvexShape a, sf::ConvexShape b)
{
	float overlap = 1000;
	sf::Vector2f smallest;
	//obtain list of axes to test as Vector2fs
	std::vector<sf::Vector2f> axes;
	for(int i = 0; i < a.getPointCount(); ++i)
	{
		sf::Vector2f vecA = a.getPoint(i);
		sf::Vector2f vecB = (i >= a.getPointCount() - 1) ? a.getPoint(0) : a.getPoint(i + 1);
		sf::Vector2f normal = sf::Vector2f((vecB.y - vecA.y), -(vecB.x - vecA.x));
		sf::Vector2f nnormal; //normalized vector
		float length = sqrt(normal.x * normal.x + normal.y * normal.y);
		if(length != 0.0f)
		{
			nnormal.x = normal.x / length;
			nnormal.y = normal.y / length;
		}
		else
		{
			nnormal = normal;
		}
			
		//std::cout<<"Normal x: "<<nnormal.x<<", Normal y: "<<nnormal.y<<std::endl;

		axes.push_back(nnormal);
	}
	
	for(int i = 0; i < b.getPointCount(); ++i)
	{
		sf::Vector2f vecA = b.getPoint(i);
		sf::Vector2f vecB = (i >= b.getPointCount() - 1) ? b.getPoint(0) : b.getPoint(i + 1);
		sf::Vector2f normal = sf::Vector2f((vecB.y - vecA.y), -(vecB.x - vecA.x));
		sf::Vector2f nnormal; //normalized vector
		float length = sqrt(normal.x * normal.x + normal.y * normal.y);
		if(length != 0.0f)
		{
			nnormal.x = normal.x / length;
			nnormal.y = normal.y / length;
		}
		else
		{
			nnormal = normal;
		}
			

		axes.push_back(nnormal);
	}

	//Project polygons onto axes, test for overlap
	for(auto it = axes.begin(); it != axes.end(); ++it)
	{
		sf::Vector2f axis = (*it);
		//get projection of shapes
		float aminimum = axis.x * a.getPoint(0).x + axis.y * a.getPoint(0).y; //dot product
		float amaximum = aminimum;
		for(int i = 1; i < a.getPointCount(); ++i)
		{
			float p = axis.x * a.getPoint(i).x + axis.y * a.getPoint(i).y;
			if(p < aminimum)
				aminimum = p;
			else if (p > amaximum)
				amaximum = p;		
		}	
		float bminimum = axis.x * b.getPoint(0).x + axis.y * b.getPoint(0).y;
		float bmaximum = bminimum;
		for(int i = 1; i < b.getPointCount(); ++i)
		{
			float p = axis.x * b.getPoint(i).x + axis.y * b.getPoint(i).y;
			if(p < bminimum)
				bminimum = p;
			else if (p > bmaximum)
				bmaximum = p;		
		}

		//check for overlap
		if(!(amaximum >= bminimum && bmaximum >= aminimum))
			return Utils::MTV{sf::Vector2f(0, 0), -1};	//false
		else
		{
			float o;
			if(amaximum <= bmaximum)
				o = abs(amaximum - bminimum);
			else
				o = abs(bmaximum - aminimum);
			if(o < overlap)
				overlap = o;
				smallest = axis;
		}
	}
	Utils::MTV theMTV{smallest, overlap};

	//no separating axis, must be colliding
	return theMTV; //true
}
