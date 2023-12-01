#pragma once

#include <SFML/Graphics.hpp>
#include "entities/Entites.h"


class EnemySpawner {

public:
	std::vector<Entities::Foe*>* foeList; 
	sf::RenderWindow* window;
	std::vector<sf::Vector2f> spawnPoints;

	float clock = 0;
	bool doClock = false;
	float timeBetweenSpawns = 3;

	EnemySpawner(std::vector<Entities::Foe*>* foeList, sf::RenderWindow* window);

	std::vector<Entities::Foe*>* GetFoes();

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

