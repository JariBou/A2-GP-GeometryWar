#pragma once

class Player;
class WaveManager;
class EnemySpawner;
class UpgradeBoxSpawner;

class GameManager {
	
	GameManager();

	void SetPlayer(Player* pPlayer) { player = pPlayer; }
	void SetWaveManager(WaveManager* pWaveManager) { waveManager = pWaveManager; }
	void SetEnemySpawner(EnemySpawner* pEnemySpawner) { enemySpawner = pEnemySpawner; }
	void SetUpgradeBoxSpawner(UpgradeBoxSpawner* pUpgradeBoxSpawner) { UpgradeBoxSpawner = pUpgradeBoxSpawner; }

	Player* GetPlayer() { return player; }
	WaveManager* GetWaveManager() { return waveManager; }
	EnemySpawner* GetEnemySpawner() { return enemySpawner; }
	UpgradeBoxSpawner* GetUpgradeBoxSpawner() { return UpgradeBoxSpawner; }

private:
	Player* player = nullptr;
	WaveManager* waveManager = nullptr;
	EnemySpawner* enemySpawner = nullptr;
	UpgradeBoxSpawner* UpgradeBoxSpawner = nullptr;
};