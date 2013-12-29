#pragma once
#include <cstdlib>
#include "sfml.h"

namespace Utils
{
	int choose(int n);
	bool isColliding(sf::ConvexShape a, sf::ConvexShape b);
	struct MTV
	{
		sf::Vector2f smallest;
	        float overlap;
	};
	MTV getCollision(sf::ConvexShape a, sf::ConvexShape b);
}
