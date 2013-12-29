#include "Player.h"


//Player::Player(void){}

Player::Player(TextureManager& texMan)
{
	playerTexture = texMan.getTexture("Player.png");
	//playerDTexture = texMan.getTexture("DPlayer.png");
	//if(!playerTexture.loadFromFile("Player.png"))
	//if(!playerDTexture.loadFromFile("DPlayer.png"))

	setTexture(playerTexture);

	//myTestObject.setTexture(playerTexture);
	//myTestObject.setPosition(46, 71);

	//setOrigin(16.0f, 16.0f);

	
	collision.setPointCount(4);
	collision.setPosition(getPosition());
	collision.setPoint(0, sf::Vector2f(0, 0));
	collision.setPoint(1, sf::Vector2f(32, 0));
	collision.setPoint(2, sf::Vector2f(32, 32));
	collision.setPoint(3, sf::Vector2f(0, 32));
	//std::cout<<"Player created."<<std::endl;
}


Player::~Player(void)
{
}

void Player::update(float dt)
{

		float hspeed = 0.0f, vspeed = 0.0f;
		//std::cout<<"PLAYER IS GOING"<<std::endl;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))

		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//setTexture(playerDTexture);
				//setTextureRect(sf::IntRect(0, 0, 32, 32));
				//if(!Collision::BoundingBoxTest(myTestObject, *this))
					hspeed = 4.0f;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//setTexture(playerDTexture);
				//setTextureRect(sf::IntRect(32, 0, 32, 32));
				//if(!Collision::BoundingBoxTest(myTestObject, *this))
					hspeed = -4.0f;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				//setTexture(playerDTexture);
				//setTextureRect(sf::IntRect(64, 0, 32, 32));
				//if(!Collision::BoundingBoxTest(myTestObject, *this))
					vspeed = -4.0f;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				//setTextureRect(sf::IntRect(96, 0, 32, 32));
				//setTexture(playerDTexture);
				//if(!Collision::BoundingBoxTest(myTestObject, *this))
					vspeed = 4.0f;
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
	
		//update collision shape
		move(hspeed * dt, vspeed * dt);
		collision.setPosition(sf::Vector2f(getPosition().x, getPosition().y)); //collision ahead of time for accurate response
		/*collision.setPoint(0, sf::Vector2f(getPosition().x, getPosition().y));
		collision.setPoint(1, sf::Vector2f(getPosition().x + 16, getPosition().y - 4));
		collision.setPoint(2, sf::Vector2f(getPosition().x + 32, getPosition().y));
		collision.setPoint(3, sf::Vector2f(getPosition().x + 32, getPosition().y + 32));
		collision.setPoint(4, sf::Vector2f(getPosition().x, getPosition().y + 32));*/
}
