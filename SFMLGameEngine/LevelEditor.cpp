#include "sfml.h"
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"

/*TODO:
 * DO THE GOD DAMN IMAGE MANAGER
 * Finish this level editor
 */

#define UP true
#define DOWN false

int currentObject;
sf::Vector2<int> currentPosition;
std::vector<GameObject*> objects;

void switchObject(bool direction)
{
	direction ? currentObject++ : currentObject--;
}

int main(int argc, char** argv)
{
	currentObject = PLAYER;
	currentPosition = sf::Vector2<int>(0, 0);
	sf::VideoMode VMode(800, 600, 32);
	sf::RenderWindow Window(VMode, "Level Editor");
	sf::Texture boxTex;
	boxTex.loadFromFile("Box.png");
	sf::Sprite box = sf::Sprite(boxTex);

	TextureManager texMan;

	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			switch (Event.type)
			{
				case sf::Event::Closed:
					Window.close();
					break;
				case sf::Event::KeyPressed:
					std::cout<<"A key was pressed :3"<<std::endl;
					if(Event.key.code == sf::Keyboard::Escape)
						Window.close();
					if(Event.key.code == sf::Keyboard::Q)
						switchObject(UP);
					if(Event.key.code == sf::Keyboard::A)
						switchObject(DOWN);
					std::cout<<"currentObject: "<<currentObject<<std::endl;

					if(Event.key.code == sf::Keyboard::Return)
					{
						GameObject* tempObject = GameObjectFactory::create(currentObject, texMan);
						tempObject->setPosition(currentPosition.x, currentPosition.y);
						objects.emplace_back(tempObject);
					}

					if(Event.key.code == sf::Keyboard::Left)
						currentPosition.x -= 16;
					if(Event.key.code == sf::Keyboard::Right)
						currentPosition.x += 16;
					if(Event.key.code == sf::Keyboard::Up)
						currentPosition.y -= 16;
					if(Event.key.code == sf::Keyboard::Down)
						currentPosition.y += 16;
					box.setPosition(currentPosition.x, currentPosition.y);
					break;
				default:
					break;
			}
		}
		Window.clear(sf::Color(128, 128, 128));
		for(auto it = objects.begin(); it < objects.end(); ++it)
		{
			Window.draw(**it);
		}
		Window.draw(box);
		Window.display();
	}
	return 0;
}
