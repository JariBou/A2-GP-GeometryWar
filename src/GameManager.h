#pragma once
#include <vector>
#include <iostream>

namespace Entities {
	class Player;
	class Bullet;
}

class WaveManager;
class EnemySpawner;
class UpgradeBoxSpawner;
class GameManager {
	
public:
	GameManager();

	void SetPlayer(Entities::Player* pPlayer) { player = pPlayer;  std::cout << "Player Set !";}
	void SetWaveManager(WaveManager* pWaveManager) { waveManager = pWaveManager; }
	void SetEnemySpawner(EnemySpawner* pEnemySpawner) { enemySpawner = pEnemySpawner; }
	void SetUpgradeBoxSpawner(UpgradeBoxSpawner* pUpgradeBoxSpawner) { UpgradeBoxSpawner = pUpgradeBoxSpawner; }

	void AddBullet(Entities::Bullet* bullet);
	std::vector<Entities::Bullet*>* GetBullets();

	std::vector<Entities::Bullet*> bulletList;
	Entities::Player* GetPlayer() { return player; }
	WaveManager* GetWaveManager() { return waveManager; }
	EnemySpawner* GetEnemySpawner() { return enemySpawner; }
	UpgradeBoxSpawner* GetUpgradeBoxSpawner() { return UpgradeBoxSpawner; }

	Entities::Player* player = nullptr;
	WaveManager* waveManager = nullptr;
	EnemySpawner* enemySpawner = nullptr;
	UpgradeBoxSpawner* UpgradeBoxSpawner = nullptr;
};