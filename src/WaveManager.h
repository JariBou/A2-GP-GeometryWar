#pragma once
#include "EnemySpawner.h"


class WaveManager
{

public:
	EnemySpawner* enemySpawner;
	float clock = 0;
	float waveCooldown = 3;
	int wave = 0;
	bool anouncing = false;
	sf::Text* anouncingText;
	WaveManager(EnemySpawner* spawner, sf::Text* anouncingWaveText);

	void SetWave(int wave, float waveCooldown);

	void Update(float deltaTime);

};