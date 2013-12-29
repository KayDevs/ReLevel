#include "Main.h"

//***TODO***//
/*
 * CHECK Implement class factory for mapfile loading
 * CHECK Implement image_manager (as described in tutorial)
 * sprites, story, etc.
 * CHECK collision system
 * Game will handle loading of images
 * CHECK Brawl-like snapback camera (hold wasd to move camera, when released it will lerp back into place)
 * TODO externalize all local variables in Main and move majority of code into functions i.e. die() reset() nextLevel() or whatever
 */

/* MF SYNTAX
   Obj
   Name
   X
   Y
   End (of file)

Ex:
Obj
Player 
24 
12
End
*/


int Main::initialize()
{
	//Not in a constructor for checking (impure)
	//prepare the window and video settings
	//create(sf::VideoMode::getFullscreenModes()[0], "SFML Tutorial Thing", sf::Style::Fullscreen);
	sf::VideoMode testingMode = sf::VideoMode(1280, 800, 32);
	create(testingMode, "ReLevel", sf::Style::Fullscreen);
	setFramerateLimit(60);

	ViewCenter = sf::Vector2<float>(getSize().x / 4.0f, getSize().y / 4.0f);
	View.setSize(sf::Vector2f(getSize().x, getSize().y));

	return EXIT_SUCCESS;
}

int Main::shutdown()
{
	return EXIT_SUCCESS;
}

int Main::run()
{
	/*sf::Texture Texture;
	  if(!Texture.loadFromFile("background.jpg"))
	  return EXIT_FAILURE;

	  for(int i = 0; i < 5; ++i)
	  {
	  gameObjects.emplace_back(new GameObject());
	  gameObjects[i]->setTexture(Texture);
	//gameObjects[i].setSpeed(0.25f);
	}*/

	/*sf::Texture BackgroundTex;
	BackgroundTex.loadFromFile("Background.png");
	sf::Sprite Background;
	Background.setTexture(BackgroundTex);*/

	Player* player = (Player*)GameObjectFactory::create("Player", texMan);
	gameObjects.emplace_back(player);

	ifstream mapfile;
	string line;
	string c;
	mapfile.open("ObjectList.txt");
	if(mapfile.is_open())
	{
		while(mapfile.good())
		{
			getline(mapfile, line);
			line.erase(remove(line.begin(), line.end(), '\t'), line.end());
			line.erase(remove(line.begin(), line.end(), '\n'), line.end());
			if(line == "Obj")
			{
				string classname, xpos, ypos;
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
					gameObjects.emplace_back(nobj);
				}
			}
			else if(line == "End")
				break;
			else
			{
				cout << "SYNTAX ERROR OR LINE BREAK DETECTED" << endl;
			}

			cout << line << endl;
		}
	}
	mapfile.close();

	float dt;
	sf::RectangleShape overlay;
	overlay.setSize(sf::Vector2f(1280, 800));
	overlay.setPosition(sf::Vector2f(ViewCenter.x - 1280/2, ViewCenter.y - 800/2));
	overlay.setFillColor(sf::Color(255, 255, 255, 0));

	while(isOpen())
	{
		sf::Event Event;
		while(pollEvent(Event))
		{
			switch(Event.type)
			{
				case sf::Event::Closed:
					close();
					shutdown();
					break;
				case sf::Event::KeyPressed:
					if(Event.key.code == sf::Keyboard::Escape)
					{
						close();
						std::cout<<"Closed."<<std::endl;
						shutdown();
						std::cout<<"Shut down."<<std::endl;
					}
					if(Event.key.code == sf::Keyboard::R)
					{
						player->setPosition(0, 0);
						overlay.setFillColor(sf::Color(255, 255, 255, 255));
						ViewCenter = sf::Vector2f(0, 0);
					}
					break;
					//case sf::Event::MouseMoved:

					//	break;
				default:
					break;
			}
		}

		//LOGIC
		deltaTime = deltaClock.restart();
		dt = deltaTime.asSeconds() * 60.0f;

		float absMouseX = sf::Mouse::getPosition(*this).x + ViewCenter.x - getSize().x / 2.0f;
		float absMouseY = sf::Mouse::getPosition(*this).y + ViewCenter.y - getSize().y / 2.0f;

		bool hasCollided = false;
		Utils::MTV coll{sf::Vector2f(0, 0), 0};
		for(int i = 0; i < (int)gameObjects.size(); ++i)
		{
			gameObjects[i]->update(dt);
			if(gameObjects[i]->solid == true /*&& !hasCollided*/) //check if object is solid and isn't already colliding with something (double collisions will move him too far)
			{
				if(Utils::isColliding(player->collision, gameObjects[i]->collision))
				{
					//std::cout<<"Player collided with something!"<<std::endl;
					Utils::MTV min = Utils::getCollision(player->collision, gameObjects[i]->collision);
					if(min.overlap > coll.overlap)
						coll = min;
					hasCollided = true;
				}
			}
		}
		if(hasCollided)
		{
			player->move(coll.smallest.x * coll.overlap, coll.smallest.y * coll.overlap);
			player->collision.setFillColor(sf::Color(255,0,0));
		}
		else
			player->collision.setFillColor(sf::Color(0,0,0));

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) 
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			float cameraSpeed = 8.0f;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (ViewCenter.x >= (player->getPosition().x + 16) - (320 - 32)))
				ViewCenter.x-=cameraSpeed * dt;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (ViewCenter.x <= (player->getPosition().x + 16) + (320 - 32)))
				ViewCenter.x+=cameraSpeed * dt;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (ViewCenter.y >= (player->getPosition().y + 16) - (200 - 32)))
				ViewCenter.y-=cameraSpeed * dt;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (ViewCenter.y <= (player->getPosition().y + 16) + (200 - 32)))
				ViewCenter.y+=cameraSpeed * dt;
		}
		else
		{
			float threshold = 8.0f;
			float cameraSpeed = 16.0f;
			//CAMERA SNAPS BACK INTO PLACE
			if((ViewCenter.x - player->getPosition().x) > threshold 
					|| (ViewCenter.y - player->getPosition().y) > threshold 
					|| (ViewCenter.x - player->getPosition().x) < -threshold 
					|| (ViewCenter.y - player->getPosition().y) < -threshold)
			{
				if(ViewCenter.x < player->getPosition().x)
					ViewCenter.x += cameraSpeed * dt;
				if(ViewCenter.x > player->getPosition().x)
					ViewCenter.x -= cameraSpeed * dt;
				if(ViewCenter.y < player->getPosition().y)
					ViewCenter.y += cameraSpeed * dt;
				if(ViewCenter.y > player->getPosition().y)
					ViewCenter.y -= cameraSpeed * dt;
			}
			else
			{
				ViewCenter = player->getPosition();
			}
		}

		View.setCenter(ViewCenter);
		setView(View);
		overlay.setPosition(sf::Vector2f(ViewCenter.x - 1280/2, ViewCenter.y - 800/2));

		//Background.setPosition(ViewCenter.x - 320, ViewCenter.y - 200);

		//GRAPHICS

		clear(sf::Color(255, 255, 255));

		//draw(Background);
		for(int i = 0; i < (int)gameObjects.size(); ++i)
		{
			//it->setPosition(100.0f, 30.0f);
			//it->setRotation(rotation);
			//gameObjects.at(1).setRotation(rotation/2);
			//gameObjects.at(0).setPosition(100.0f, 30.0f);
			//it->setScale(.25f, .25f);
			//gameObjects[i]->setColor(sf::Color(255, 255, 255, 128));
			draw(*gameObjects[i]);
			//draw(gameObjects[i]->collision);
		}

		if(overlay.getFillColor().a > 0)
			overlay.setFillColor(sf::Color(255,255,255,overlay.getFillColor().a - 4 * dt));
		if(overlay.getFillColor().a < 0)
			overlay.setFillColor(sf::Color(255,255,255,0));

		draw(overlay);
		display();
	}

	if(shutdown())
		return EXIT_SUCCESS;
	return EXIT_FAILURE;
}

int main(int argc, char** argv)
{
	Main theMain;
	if(theMain.initialize() == 0)
	{
		std::cout<<"Initialized."<<std::endl;
		return theMain.run();
	}
		
	return EXIT_FAILURE;
}
