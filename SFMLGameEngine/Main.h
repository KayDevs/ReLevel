#include "sfml.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Player.h"
#include "TextureManager.h"
#include "Utils.h"

using namespace std;
class Main : public sf::RenderWindow
{
public:
	int initialize(void);
	int shutdown(void);
	int run(void);

	sf::View View;
	sf::Vector2<float> ViewCenter;

	sf::Clock deltaClock;
	sf::Time deltaTime;
	
	TextureManager texMan;

	std::vector<std::unique_ptr<GameObject>> gameObjects;
};
