#include "Player.h"


Player::Player(void)
{
	if(!playerTexture.loadFromFile("Player.png"))
	{
		std::cout<<"Failed to load image Player.png"<<std::endl;
	}
	if(!playerDTexture.loadFromFile("DPlayer.png"))
	{
		std::cout<<"Failed to load image DPlayer.png"<<std::endl;
	}
	setTexture(playerTexture);

	myTestObject.setTexture(playerTexture);
	myTestObject.setPosition(46, 71);

	//setOrigin(16.0f, 16.0f);

	//std::cout<<"Player created."<<std::endl;
}

Player::Player(float x, float y)
{
	if(!playerTexture.loadFromFile("Player.png"))
	{
		std::cout<<"Failed to load image Player.png"<<std::endl;
	}
	if(!playerDTexture.loadFromFile("DPlayer.png"))
	{
		std::cout<<"Failed to load image DPlayer.png"<<std::endl;
	}
	setTexture(playerTexture);

	setPosition(x, y);
	//myTestObject.setTexture(playerTexture);
	//myTestObject.setPosition(46, 71);

	//setOrigin(16.0f, 16.0f);

	//std::cout<<"Player created."<<std::endl;
}


Player::~Player(void)
{
}

void Player::update(float dt)
{
		//std::cout<<"PLAYER IS GOING"<<std::endl;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))

		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				setTexture(playerDTexture);
				setTextureRect(sf::IntRect(0, 0, 32, 32));
				//if(!Collision::BoundingBoxTest(myTestObject, *this))
					move(4.0f * dt, 0);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				setTexture(playerDTexture);
				setTextureRect(sf::IntRect(32, 0, 32, 32));
				//if(!Collision::BoundingBoxTest(myTestObject, *this))
					move(-4.0f * dt, 0);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				setTexture(playerDTexture);
				setTextureRect(sf::IntRect(64, 0, 32, 32));
				//if(!Collision::BoundingBoxTest(myTestObject, *this))
					move(0, -4.0f * dt);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				setTextureRect(sf::IntRect(96, 0, 32, 32));
				setTexture(playerDTexture);
				//if(!Collision::BoundingBoxTest(myTestObject, *this))
					move(0, 4.0f * dt);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				scale(2.0f, 2.0f);
			}
		}
		else
		{
			setRotation(0.0f);
			setTexture(playerTexture);
			setTextureRect(sf::IntRect(0, 0, 32, 32));
		}
}