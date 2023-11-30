#include "Player.h"
#include "DrawableEntity.h"
#include "Bullet.h"
#include "../utils.h"
#include <iostream>


namespace Entities 
{
	using namespace std;
	sf::Clock frameClock;


	Player::Player(sf::Shape& shape) : DrawableEntity(shape){
	}
	
	

	void Player::MovePlayer()
	{
		sf::FloatRect boundingBox = shape.getLocalBounds();
		playerWidth = boundingBox.width;
		playerHeight = boundingBox.height;

		//cout << "player Witdh : " << playerHeight << ", player Height : " << playerHeight << endl;
		//cout << "x : " << shape.getPosition().x << ", y :" << shape.getPosition().y << endl;
		//cout << "Window Height : " << windowHeight << ", Window Width : " << windowWidth << endl << endl;
		sf::Vector2f moveVector;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			if (shape.getPosition().y - 1 > 0) {
				moveVector.y = -1;
			}
			/*moveVector.y = -1;*/
		}

			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if ((shape.getPosition().y + playerHeight) + 1 < windowHeight) {
				moveVector.y = 1;
			}
			/*moveVector.y = 1;*/
		}	

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if (shape.getPosition().x - 1 > 0)
			{
				moveVector.x = -1;
			}
			/*moveVector.x = -1;*/
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if ((shape.getPosition().x + playerWidth) + 1 < windowWidth)
			{
				moveVector.x = 1;
			}
			//moveVector.x = 1;
		}

		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;
		Move(Utils::NormalizeVector(moveVector) * cubeSpeed * deltaTime);
	}

	void Player::ShootPlayer()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMouseClickedLastFrame) {
			cout << "Cliqued" << endl;

			sf :: RectangleShape* rectangleBullet = new sf::RectangleShape(sf::Vector2f(5, 5));
			Bullet* bullet = new Bullet(*rectangleBullet);
			(*bullet).SetColor(sf::Color::Red);
			bullet -> SetPosition(sf::Vector2f(shape.getPosition().x + playerWidth / 2, shape.getPosition().y - shape.getLocalBounds().height));
			bullets.push_back(bullet);

			isMouseClickedLastFrame = true;
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			isMouseClickedLastFrame = false;
		}
	}


	std::vector<Bullet*> Player::GetBullets() 
	{
		return bullets;
	}
}



