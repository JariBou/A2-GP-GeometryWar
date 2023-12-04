#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "entities/UpgradeBox.h"
#include "entities/DrawableEntity.h"
#include "utils.h"
#include <iostream>


class UpgradeBoxSpawner {
	public :
		UpgradeBoxSpawner(std::vector<Entities::UpgradeBox*>& upgradeBoxList, int WindowWidth, Entities::Player& Player);
		~UpgradeBoxSpawner() = default;
		virtual void SpawnUpgradeBox();
		virtual void SpawnUpgradeBox(sf::Shape* shape);
		std::vector<Entities::UpgradeBox*>& GetUpgradeBoxList();
		std::vector<Entities::DrawableEntity*>& GetUpgradeBoxEntities();
		int windowWidth; 
		Entities::Player* player;
		void Update(float deltaTime);
		float spawnCooldown = 2;
		float spawnTimer = 0;

		void TrySpawning(float deltaTime);
		
	private:
		std::vector<Entities::UpgradeBox*> upgradeBoxList;

};