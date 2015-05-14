#include "Main.h"

//***TODO***//
/*
 * Reorganize FileSystem.
		-create /res
		-create /bin and /src that both reference ../res
 * CHECK enemies
 * Spikes, timed beams, nonmoving obstacles, etc.
 * CHECK Implement class factory for mapfile loading
 * CHECK Implement image_manager (as described in tutorial)
 * CHECK collision system
 * CHECK Brawl-like snapback camera (hold wasd to move camera, when released it will lerp back into place)
 * TODO externalize all local variables in Main and move majority of code into functions i.e. die() reset() nextLevel() or whatever
 * C++ify. Less C and more C++ correctness
 * Externalize into LevelData class designed to work with files and contain the arrays GameObjects, Killers, Solids, as well as track references to the player and other important items.
 * LevelData should have create, destroy, update, and draw methods that will be called by the Main
 * Add console command system to interface with the LevelData, to allow for adding/removing objects at runtime
 */

/*
  CURRENT PROBLEMS!!
  -running speed is inversely porportional to the number of things on the screen - this could be anything:
     - graphics (too many polygons)
     - faulty memory handling
     - collision testing slowing shit down
     (test on lower/higher resolutions to confirm the latter two - if it's a graphical problem then it will worsen with screen resolution allegedly - though that might just add to the overhead introduced with the formerly stated problems)
     further testing is required.
  -not optimized, but save optimization for later seeing as things need to be actually done first
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
	create(testingMode, "ReLevel", sf::Style::Titlebar);
	setFramerateLimit(60);

	//ViewCenter = sf::Vector2<float>(getSize().x / 4.0f, getSize().y / 4.0f);
	ViewCenter = sf::Vector2f(0, 0);
	View.setSize(sf::Vector2f(getSize().x, getSize().y));
	return EXIT_SUCCESS;
}

int Main::shutdown()
{
	return EXIT_SUCCESS;
}

int Main::run()
{
	Player* player = dynamic_cast<Player*>(GameObjectFactory::create("Player", texMan));
	player->setPosition(0.0f, 0.0f);
	player->grav = 0.0f;
	player->inAir = false;
	gameObjects.emplace_back(player);

	ifstream mapfile;
	string line;
	string c;
	mapfile.open("ObjectList.txt"); //change to argv[1]
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
				std::cout<<classname<<std::endl;
				std::cout<<stoi(xpos)<<std::endl;
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

	float dt = 0.0f;
	deltaClock.restart();
	sf::RectangleShape overlay;
	overlay.setSize(sf::Vector2f(1280, 800));
	overlay.setPosition(sf::Vector2f(ViewCenter.x - 1280/2, ViewCenter.y - 800/2));
	overlay.setFillColor(sf::Color(255, 255, 255, 0));
	float overlayAlpha = 255;

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
					player->grav = 0.0f;
					player->vspeed = 0.0f;
					player->hspeed = 0.0f;
					overlayAlpha = 255;
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

		for(int i = 0; i < (int)gameObjects.size(); ++i)
		{
			gameObjects[i]->update(dt);
			gameObjects[i]->updateCollision(dt, gameObjects);
		}
		if(player->killed == true)
		{
			overlayAlpha = 255;
			ViewCenter = sf::Vector2f(0, 0);
		}


		//float absMouseX = sf::Mouse::getPosition(*this).x + ViewCenter.x - getSize().x / 2.0f;
		//float absMouseY = sf::Mouse::getPosition(*this).y + ViewCenter.y - getSize().y / 2.0f;


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		   || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			float cameraSpeed = 8.0f;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (ViewCenter.x >= (player->getPosition().x + 16) - (320 - 32)))
				ViewCenter.x-=cameraSpeed;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (ViewCenter.x <= (player->getPosition().x + 16) + (320 - 32)))
				ViewCenter.x+=cameraSpeed;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (ViewCenter.y >= (player->getPosition().y + 16) - (200 - 32)))
				ViewCenter.y-=cameraSpeed;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (ViewCenter.y <= (player->getPosition().y + 16) + (200 - 32)))
				ViewCenter.y+=cameraSpeed;
		}
		else
		{
			float threshold = 32.0f;
			float cameraSpeed = 16.0f;
			if((ViewCenter.x - player->getPosition().x) > threshold
			   || (ViewCenter.y - player->getPosition().y) > threshold
			   || (ViewCenter.x - player->getPosition().x) < -threshold
			   || (ViewCenter.y - player->getPosition().y) < -threshold)
			{
				if(ViewCenter.x < player->getPosition().x)
					ViewCenter.x += cameraSpeed;
				if(ViewCenter.x > player->getPosition().x)
					ViewCenter.x -= cameraSpeed;
				if(ViewCenter.y < player->getPosition().y)
					ViewCenter.y += cameraSpeed;
				if(ViewCenter.y > player->getPosition().y)
					ViewCenter.y -= cameraSpeed;
			}
			else
			{
				ViewCenter = player->getPosition();
			}
		}


		//ViewCenter = player->getPosition();

		View.setCenter(ViewCenter);
		setView(View);
		overlay.setPosition(sf::Vector2f(ViewCenter.x - 1280/2, ViewCenter.y - 800/2));


		//GRAPHICS

		clear(sf::Color(255, 255, 255));

		for(int i = 0; i < (int)gameObjects.size(); ++i)
		{
			draw(*gameObjects[i]);
			//draw(gameObjects[i]->collision);
		}

		if(overlayAlpha > 0)
			overlayAlpha -= 8.0f;
		if(overlayAlpha <= 0)
		{
			overlayAlpha = 0.0f;
		}
		overlay.setFillColor(sf::Color(255,255,255,overlayAlpha));

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
