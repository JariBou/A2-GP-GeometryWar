#include "Boss1.h"
#include "Bullet.h"
#include "../GameManager.h"
#include "../utils.h"

Entities::Boss1::Boss1(sf::Shape& shape, float speed, float health, GameManager* gameManager) : Foe(shape, speed, gameManager)
{
	this->health = health;
}

void Entities::Boss1::Update(float deltaTime)
{
	this->shootingClock += deltaTime;
	if (this->BigShotClock >= this->BigShotCooldown) {
		this->BigShotCooldown = 0;

		sf::RectangleShape* rectangleBullet = new sf::RectangleShape(sf::Vector2f(20, 20));
		 
		sf::Vector2f direction(Utils::GetShapeCenter(this->gameManager->GetPlayer()->shape) - Utils::GetShapeCenter(this->shape)); 

		Bullet* bullet = new Bullet(*rectangleBullet, this->gameManager, 5, 500.0, direction, windowDimension.x); 
		(*bullet).SetColor(sf::Color::Green); 
		auto selfRect = shape.getGlobalBounds();
		bullet->SetPosition(sf::Vector2f(selfRect.left + selfRect.width / 2 - rectangleBullet->getSize().x / 2,
			selfRect.top + selfRect.height));
		bullet->ShotByEnemy(); 
		this->gameManager->AddBullet(bullet); 
	}
	if (this->shootingClock >= this->shootingCooldown) {
		this->shootingClock = 0;
		sf::RectangleShape* rectangleBullet = new sf::RectangleShape(sf::Vector2f(5, 5));

		sf::Vector2f direction(Utils::GetShapeCenter(this->gameManager->GetPlayer()->shape) - Utils::GetShapeCenter(this->shape));

		Bullet* bullet = new Bullet(*rectangleBullet, this->gameManager, 1, 700.0, direction, windowDimension.x);
		(*bullet).SetColor(sf::Color::Green);
		auto selfRect = shape.getGlobalBounds();
		bullet->SetPosition(sf::Vector2f(selfRect.left + selfRect.width / 2 - rectangleBullet->getSize().x / 2,
			selfRect.top + selfRect.height));
		bullet->ShotByEnemy();
		this->gameManager->AddBullet(bullet);
	}
}

bool Entities::Boss1::isDead()
{
	return this->health <= 0;
}

void Entities::Boss1::OnKilledByPlayer()
{
}

bool Entities::Boss1::IsOutOfBounds()
{
	return false;
}
