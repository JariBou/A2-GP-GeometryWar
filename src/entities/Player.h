#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "Bullet.h"

class EnemySpawner;
class DrawableEntity;

namespace Entities
{
	constexpr float cubeSpeed = 500.f;

	class Player : public DrawableEntity {

		public:

			int upgradeLevel = 0;
			bool upgraded;
			int lives = 3;
			float bulletCooldown = 0.5f;
			float bulletClock;
			float nbBulletShot = 1;
			Player(sf::Shape& shape);
			virtual ~Player() = default;
			virtual void MovePlayer(float deltaTime);
			virtual void Update(float deltaTime);
			virtual void UpgradeLevel();
			virtual std::vector<Bullet*>& GetBullets();
			float playerWidth;
			float playerHeight;
			EnemySpawner* enemySpawner;
			virtual EnemySpawner* GetSpawner();


			void Draw(sf::RenderWindow& window);

		private:
			std::vector<Bullet*> bullets;
			bool isMouseClickedLastFrame;
	
	};
}