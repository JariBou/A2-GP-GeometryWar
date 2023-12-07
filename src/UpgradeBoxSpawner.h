#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "utils.h"
#include "GameManager.h"

namespace Entities {
	class DrawableEntity;
	class UpgradeBoc;
	class Player;
}


class UpgradeBoxSpawner {
	public :
		UpgradeBoxSpawner(std::vector<Entities::UpgradeBox*>& upgradeBoxList, int WindowWidth, GameManager* pGameManager);
		~UpgradeBoxSpawner() = default;
		//virtual void SpawnUpgradeBox();
		virtual void SpawnUpgradeBox(sf::Shape* shape);
		std::vector<Entities::UpgradeBox*>& GetUpgradeBoxList();
		std::vector<Entities::DrawableEntity*>& GetUpgradeBoxEntities();
		int windowWidth; 
		Entities::Player* player;
		void Update(float deltaTime);
		float spawnCooldown = 2;
		float spawnTimer = 0;
		GameManager* gameManager;

		//void TrySpawning(float deltaTime);
		
	private:
		std::vector<Entities::UpgradeBox*> upgradeBoxList;

};