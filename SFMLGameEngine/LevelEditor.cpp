#include "sfml.h"
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"
#include <string>
#include <fstream>

/*TODO:
 * File I/O for this level editor
 */

#define UP true
#define DOWN false

int currentObject;
sf::Vector2<int> currentPosition;
std::vector<GameObject*> objects;
std::vector<std::string> objectnames;
std::vector<float> xs;
std::vector<float> ys;

void switchObject(bool direction)
{
	direction ? currentObject++ : currentObject--;
}
std::string objectToString(int object)
{
	if(object==0)
		return "Player";
	if(object==1)
		return "BasicEnemy";
	if(object==2)
		return "Block";
	if(object==3)
		return "LSlope";
	if(object==4)
		return "RSlope";
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

	std::string mapfilename;
	if (argc > 1)
		mapfilename = argv[1];
	std::ifstream mapfile;
	std::string line;
	std::string c;
	mapfile.open(mapfilename);
	if(mapfile.is_open())
	{
		while(mapfile.good())
		{
			getline(mapfile, line);
			line.erase(remove(line.begin(), line.end(), '\t'), line.end());
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			if(line == "Obj")
			{
				std::string classname, xpos, ypos;
				getline(mapfile, classname);
				classname.erase(remove(classname.begin(), classname.end(), '\t'), classname.end());
				getline(mapfile, xpos);
				xpos.erase(remove(xpos.begin(), xpos.end(), '\t'), xpos.end());
				getline(mapfile, ypos);
				ypos.erase(remove(ypos.begin(), ypos.end(), '\t'), ypos.end());
				GameObject* nobj = GameObjectFactory::create(classname, texMan);
				if(nobj)
				{
					nobj->setPosition(stoi(xpos), stoi(ypos));
					objects.emplace_back(nobj);
					objectnames.emplace_back(classname);
					xs.emplace_back(stoi(xpos));
					ys.emplace_back(stoi(ypos));
				}
			}
			else if(line == "End")
				break;
			else
			{
				std::cout << "SYNTAX ERROR OR LINE BREAK DETECTED" << std::endl;
			}

			std::cout << line << std::endl;
		}
	}
	mapfile.close();
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
					if(Event.key.code == sf::Keyboard::S)
					{
						std::ofstream mapout(mapfilename, std::ios::trunc);
						for(int i = 0; i < objects.size(); ++i)
						{
							mapout<<"Obj"<<std::endl;
							mapout<<objectnames[i]<<std::endl;
							mapout<<xs[i]<<std::endl;
							mapout<<ys[i]<<std::endl;
						}
						mapout<<"End"<<std::endl;
						mapout.close();
					}
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
						objectnames.emplace_back(objectToString(currentObject));
						xs.emplace_back(currentPosition.x);
						ys.emplace_back(currentPosition.y);
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
