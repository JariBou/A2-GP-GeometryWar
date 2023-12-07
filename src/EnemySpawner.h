#pragma once

#include <SFML/Graphics.hpp>
#include "enum.h"

namespace Entities {
	class Player;
	class Foe;
	class DrawableEntity;
}

class Spawnpoint;

class EnemySpawner {

public:
	std::vector<Entities::Foe*>* foeList; 
	sf::RenderWindow* window;
	std::vector<Spawnpoint*> spawnPoints;
	Entities::Player* player;

	float clock = 0;
	bool doClock = false;
	float timeBetweenSpawns = 3;

	EnemySpawner(std::vector<Entities::Foe*>* foeList, sf::RenderWindow* window, Entities::Player* player);

	std::vector<Entities::Foe*>* GetFoes();

	std::vector<Entities::DrawableEntity*>& GetFoeEntities();

	void SpawnEnemy();
	void SpawnEnemy(int i);
	void SpawnEnemy(sf::Vector2f position, EnemyType enemyType);
	
	void setSpawnPoints(std::vector<Spawnpoint*> points) {
		for (Spawnpoint* point : spawnPoints) {
			delete point;
		}
		spawnPoints.clear();
		spawnPoints = points;
	}
	
	void Update(float deltaTime);

	void StartClock() {
		doClock = true;
	}

	void StopClock() {
		doClock = false;
	}

	void ResetClock() {
		clock = 0;
	}

};

