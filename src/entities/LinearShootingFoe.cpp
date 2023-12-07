#include "LinearShootingFoe.h"
#include <iostream>
#include "../utils.h"
#include "Bullet.h"
#include "Player.h"

namespace Entities
{

	LinearShootingFoe::LinearShootingFoe(sf::Shape& shape, float speed, Player* player) : LinearFoe(shape, speed, player) {
	}

	void LinearShootingFoe::Update(float deltaTime){
		LinearFoe::Update(deltaTime);

		if (this->bullets.size() > 0) {
			Utils::CheckBulletListLife(this->bullets);
			for (Entities::Bullet* bullet : this->bullets)
			{
				bullet->Update(deltaTime);
			}
		}

		this->shootingClock += deltaTime;
		if (this->shootingClock >= this->shootingCooldown) {
			this->shootingClock = 0;
			sf::RectangleShape* rectangleBullet = new sf::RectangleShape(sf::Vector2f(5, 5));
			Bullet* bullet = new Bullet(*rectangleBullet, *this->player, 1, 600.0, sf::Vector2f(0, 1), windowWidth);
			(*bullet).SetColor(sf::Color::Green);
			auto selfRect = shape.getGlobalBounds();
			bullet->SetPosition(sf::Vector2f(selfRect.left + selfRect.width/2 - rectangleBullet->getSize().x/2,
				selfRect.top + selfRect.height));
			bullet->ShotByEnemy();
			this->bullets.push_back(bullet);
		}
	}

	void LinearShootingFoe::Draw(sf::RenderWindow& window) {
		LinearFoe::Draw(window);

		for (Entities::Bullet* bullet : this->bullets)
		{
			bullet->Draw(window);
		}
	}
}