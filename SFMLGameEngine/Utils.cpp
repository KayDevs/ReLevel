#include "Utils.h"

//Utils::function = ;

//SAT classes

struct Point
{
	float x, y;
	Point(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

class Shape
{
public:
	std::vector<Point> points;
	int numPoints;
};

struct Axis
{
	float x1, y1, x2, y2;
	Axis(float _x1, float _y1, float _x2, float _y2)
	{
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}
};

struct Projection
{
	float x1, x2;
	Projection(float _x1, float _x2)
	{
		x1 = _x1;
		x2 = _x2;
	}
};

int Utils::choose(int n)
{
	return (rand() % (n - 1)) + 1;
}