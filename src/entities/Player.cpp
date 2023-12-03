#include "Player.h"
#include "DrawableEntity.h"
#include "Bullet.h"
#include "../utils.h"
#include <iostream>


namespace Entities 
{
	using namespace std;


	Player::Player(sf::Shape& shape) : DrawableEntity(shape){
	}
	

	void Player::MovePlayer(float deltaTime)
	{
		sf::FloatRect boundingBox = shape.getLocalBounds();
		playerWidth = boundingBox.width + shape.getOutlineThickness()/2;
		playerHeight = boundingBox.height + shape.getOutlineThickness()/2;

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

		//std::cout << 1.f / deltaTime << " FPS" << std::endl;
		Move(Utils::NormalizeVector(moveVector) * speed, deltaTime);
	}
    
    void Player::Draw(sf::RenderWindow& window){
		window.draw(this->shape);

		//Hitbox
		sf::RectangleShape rect;
		rect.setPosition(this->shape.getGlobalBounds().left, this->shape.getGlobalBounds().top);
		rect.setSize(sf::Vector2f(this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().height));
		rect.setOutlineThickness(2);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::White);
		window.draw(rect);
	}

	void Player::Update(float deltaTime)
	{
		bulletClock += deltaTime;
		if (bulletClock >= bulletCooldown - upgradeLevel / 4 * 0.15) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				bulletClock = 0;
				cout << "Cliqued" << endl;

				float bulletSize = 5 + upgradeLevel / 4 * 5;
				float w = playerWidth / (pow(2, upgradeLevel % 4) + 1) - bulletSize/2;
				for (size_t i = 1; i < pow(2,upgradeLevel % 4) + 1; i++)
				{
					sf :: RectangleShape* rectangleBullet = new sf::RectangleShape(sf::Vector2f(bulletSize,bulletSize));
					float bulletSpeed = speed + 250.0 * (upgradeLevel + 1) / 8;
                    Bullet* bullet = new Bullet(*rectangleBullet, *this, 10, bulletSpeed, sf::Vector2f(0, -1.0), windowWidth);
					bullet->SetColor(sf::Color::Red);
					bullet->SetPosition(sf::Vector2f(shape.getPosition().x + i*w , shape.getPosition().y - rectangleBullet->getSize().y * 1.5));
					bullets.push_back(bullet);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && !upgraded) { UpgradeLevel(); }
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && upgraded) { upgraded = false; }
	}

	void Player::UpgradeLevel()
	{
		if (upgradeLevel < 15){
			upgradeLevel++;
			upgraded = true;
			cout << "Upgrade level : " << upgradeLevel << endl;
		}

	}

	void Player::GetHit(float damage) {
		std::cout << "Player hit" << std::endl;
	}

	EnemySpawner* Player::GetSpawner() {
		return this->enemySpawner;
	}

	std::vector<Bullet*>& Player::GetBullets() 
	{
		return bullets;
	}

	std::vector<DrawableEntity*>& Player::GetBulletEntities()
	{
		std::vector<DrawableEntity*> vec;
		for (Bullet* bullet : bullets) {
			vec.push_back(bullet);
		}
		return vec;
	}
}
	




	