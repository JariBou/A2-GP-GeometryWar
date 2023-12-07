#pragma once


class Player;
class WaveManager;
class EnemySpawner;
class UpgradeBoxSpawner;

class GameManager {
	
public:
	GameManager();

	void SetPlayer(Entities::Player* pPlayer) { player = pPlayer; }
	void SetWaveManager(WaveManager* pWaveManager) { waveManager = pWaveManager; }
	void SetEnemySpawner(EnemySpawner* pEnemySpawner) { enemySpawner = pEnemySpawner; }
	void SetUpgradeBoxSpawner(UpgradeBoxSpawner* pUpgradeBoxSpawner) { UpgradeBoxSpawner = pUpgradeBoxSpawner; }

	Entities::Player* GetPlayer() { return player; }
	WaveManager* GetWaveManager() { return waveManager; }
	EnemySpawner* GetEnemySpawner() { return enemySpawner; }
	UpgradeBoxSpawner* GetUpgradeBoxSpawner() { return UpgradeBoxSpawner; }

private:
	Entities::Player* player = nullptr;
	WaveManager* waveManager = nullptr;
	EnemySpawner* enemySpawner = nullptr;
	UpgradeBoxSpawner* UpgradeBoxSpawner = nullptr;
};