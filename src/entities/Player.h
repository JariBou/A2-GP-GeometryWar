#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "Bullet.h"

class EnemySpawner;
class UpgradeBoxSpawner;
class DrawableEntity;

namespace Entities
{
	class Player : public DrawableEntity {

		public:

			int upgradeLevel = 0;
			bool upgraded;
			int lives = 3;
			float bulletCooldown = 0.5f;
			float bulletClock = 0;
			float nbBulletShot = 1;
			float speed = 450.0;
			Player(sf::Shape& shape);
			virtual ~Player() = default;
			virtual void MovePlayer(float deltaTime);
			virtual void Update(float deltaTime);
			virtual void UpgradeLevel();
			virtual std::vector<Bullet*>& GetBullets();
			std::vector<DrawableEntity*>& GetBulletEntities();
			float playerWidth;
			float playerHeight;
			virtual EnemySpawner* GetEnemySpawner();
			virtual UpgradeBoxSpawner* GetBoxSpawner();

			virtual void GetHit(float damage);

			void Draw(sf::RenderWindow& window);

			void SetEnemySpawner(EnemySpawner* spawner);
			void SetBoxSpawner(UpgradeBoxSpawner* spawner);

		private:
			EnemySpawner* enemySpawner = nullptr;
			UpgradeBoxSpawner* boxSpawner = nullptr;
			std::vector<Bullet*> bullets;
			bool isMouseClickedLastFrame;
	
	};
}