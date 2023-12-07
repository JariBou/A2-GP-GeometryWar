#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "../enum.h"


class EnemySpawner;
class UpgradeBoxSpawner;

namespace Entities
{
	class Bullet;

	class Player : public DrawableEntity {

		public:

			int upgradeLevel = 0;
			bool upgraded;
			int lives = 3;

			//Upgradable Variables
			float bulletCooldown = 0.5f;
			sf::Vector2f bulletSize = sf::Vector2f(5, 5);
			float bulletClock = 0;
			float nbBulletShot = 1;
			float speed = 450.0;
			float bulletDamage = 10;

			Player(sf::Shape& shape);
			virtual ~Player() = default;
			virtual void MovePlayer(float deltaTime);
			virtual void Update(float deltaTime);
			virtual void UpgradeLevel(UpgradeType type);
			virtual std::vector<Bullet*>& GetBullets();
			std::vector<DrawableEntity*>& GetBulletEntities();
			float playerWidth;
			float playerHeight;
			virtual EnemySpawner* GetEnemySpawner();
			virtual UpgradeBoxSpawner* GetBoxSpawner();

			virtual void GetHit(float damage);

			/// <summary>
			/// Returns False if the entity should be removed
			/// </summary>
			/// <returns></returns>
			virtual bool CheckLife();

			void Draw(sf::RenderWindow& window);

			void SetEnemySpawner(EnemySpawner* spawner);
			void SetBoxSpawner(UpgradeBoxSpawner* spawner);
			int bulletDamageLevel = 1;
			int bulletNumberLevel = 1;
			int movementSpeedLevel = 1;
			int bulletSpeedLevel = 1;

		private:
			EnemySpawner* enemySpawner = nullptr;
			UpgradeBoxSpawner* boxSpawner = nullptr;
			std::vector<Bullet*> bullets;
			std::vector<float> bulletAngles;
			int chanceCount = 3; // Toutes les trois erreurs (pris un dégât ou enemie passe en bas de l'écran) le joueur perd une vie
	
	};
}