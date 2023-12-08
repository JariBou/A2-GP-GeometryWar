#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entities {
	class Player;
	class Bullet;
}

namespace SFX {
	class ParticleSystem;
}

class WaveManager;
class EnemySpawner;
class UpgradeBoxSpawner;
class GameManager {
	
public:
	GameManager(sf::RenderWindow& window);

	void SetPlayer(Entities::Player* pPlayer) { player = pPlayer;  std::cout << "Player Set !";}
	void SetWaveManager(WaveManager* pWaveManager) { waveManager = pWaveManager; }
	void SetEnemySpawner(EnemySpawner* pEnemySpawner) { enemySpawner = pEnemySpawner; }
	void SetUpgradeBoxSpawner(UpgradeBoxSpawner* pUpgradeBoxSpawner) { UpgradeBoxSpawner = pUpgradeBoxSpawner; }
	void SetParticleSystem(SFX::ParticleSystem* pParticleSystem) { particleSystem = pParticleSystem; }
	void Reset();
	
	void AddBullet(Entities::Bullet* bullet);
	std::vector<Entities::Bullet*>* GetBullets();

	std::vector<Entities::Bullet*> bulletList;
	Entities::Player* GetPlayer() { return player; }
	sf::Vector2f GetWindowDimension() { return windowDimension; }
	WaveManager* GetWaveManager() { return waveManager; }
	EnemySpawner* GetEnemySpawner() { return enemySpawner; }
	UpgradeBoxSpawner* GetUpgradeBoxSpawner() { return UpgradeBoxSpawner; }
	SFX::ParticleSystem* GetParticleSystem() { return particleSystem; }

	sf::Vector2f windowDimension;
	Entities::Player* player = nullptr;
	WaveManager* waveManager = nullptr;
	EnemySpawner* enemySpawner = nullptr;
	UpgradeBoxSpawner* UpgradeBoxSpawner = nullptr;
	SFX::ParticleSystem* particleSystem = nullptr;
};