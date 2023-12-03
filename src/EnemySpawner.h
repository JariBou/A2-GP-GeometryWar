#pragma once

#include <SFML/Graphics.hpp>
#include "entities/Entites.h"

class Player;

class EnemySpawner {

public:
	std::vector<Entities::Foe*>* foeList; 
	sf::RenderWindow* window;
	std::vector<sf::Vector2f> spawnPoints;
	Entities::Player* player;

	float clock = 0;
	bool doClock = false;
	float timeBetweenSpawns = 3;

	EnemySpawner(std::vector<Entities::Foe*>* foeList, sf::RenderWindow* window, Entities:: Player* player);

	std::vector<Entities::Foe*>* GetFoes();

	std::vector<Entities::DrawableEntity*>& GetFoeEntities();

	void SpawnEnemy();
	void SpawnEnemy(int i);
	void SpawnEnemy(sf::Vector2f position);
	
	void setSpawnPoints(std::vector<sf::Vector2f> points) {
		spawnPoints = points;
	}
	
	void Update(float deltaTime) {
		if (doClock) {
			clock += deltaTime;
			if (clock >= timeBetweenSpawns) {
				SpawnEnemy(spawnPoints[std::rand() % spawnPoints.size()]);
				ResetClock();
			}
		}
	}

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

