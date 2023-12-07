#include "WaveManager.h"
#include <iostream>
#include "utils.h"
#include "Spawnpoint.h"
#include "EnemySpawner.h"

WaveManager::WaveManager(EnemySpawner* spawner, sf::Text* anouncingWaveText)
{
	enemySpawner = spawner;
	anouncingText = anouncingWaveText;
}

void WaveManager::SetWave(int wave, float waveCooldown)
{
	this->wave = wave;
	this->waveCooldown = waveCooldown;
	std::vector<Spawnpoint*> spawnPoints;
	enemySpawner->StopClock();
	anouncingText->setString("Wave " + Utils::toString(wave));
	anouncingText->setScale(sf::Vector2f(0,0));
	anouncing = true;
	switch (wave)
	{
	case 0:
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));
		break;
	case 1:
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));
		for (size_t i = 0; i < spawnPoints.size(); i++)
		{
			spawnPoints[i]->AddEnemyToSpawn(NonLinearFoe, 20);
		}
		break;
	default:
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));
		break;
	}
	enemySpawner->setSpawnPoints(spawnPoints);
}

void WaveManager::Update(float deltaTime)
{
	clock += deltaTime;
	if (anouncing) {
		sf::Vector2f scale = anouncingText->getScale();
		scale.x += 0.4f * deltaTime;
		scale.y += 0.4f * deltaTime;
		anouncingText->setScale(scale);
		if (scale.x >= 1) {
			enemySpawner->StartClock();
			anouncing = false;
			clock = 0;
		}
	}
	else if (clock >= waveCooldown) {
		this->SetWave(wave + 1, waveCooldown);
	}
}
