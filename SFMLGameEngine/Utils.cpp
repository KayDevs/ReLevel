#include "Utils.h"

//Utils::function = ;

int Utils::choose(int n)
{
	//TODO: FUCKING SAT ALREADY JEEZ USE SFML's shape classes
	//list of axes are the polygon's normals 
	//normals obtained by flipping coordinates and negating one, then normalizing
	//i.e. (x, y) -> (-y, x) or (y, -x)
	//projections obtained by finding min. and max. vertex in polygon relative to axis
	//loop over axes to obtain whether or not projections overlap, if they don't, no collision exit immediately
	return (rand() % (n - 1)) + 1;
}
