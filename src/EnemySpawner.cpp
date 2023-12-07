#include "EnemySpawner.h"
#include "entities/Entites.h"
#include "Spawnpoint.h"


EnemySpawner::EnemySpawner(std::vector<Entities::Foe*>* foeList, sf::RenderWindow* window, Entities::Player* player) {
	this->foeList = foeList;
	this->window = window;
	this->player = player;
}

// Yeah so mb We'll have to live with this one being a pointer 'till someone changes it
std::vector<Entities::Foe*>* EnemySpawner::GetFoes() {
	return this->foeList;
}

std::vector<Entities::DrawableEntity*>& EnemySpawner::GetFoeEntities()
{
	std::vector<Entities::DrawableEntity*> vec;
	for (Entities::Foe* foe : *foeList) {
		vec.push_back(foe);
	}
	return vec;
}

void EnemySpawner::Update(float deltaTime) {
	if (doClock) {
		int spawnpointIndex = std::rand() % spawnPoints.size();	
		clock += deltaTime;
		if (clock >= timeBetweenSpawns) {
			EnemyType enemyType = LinearShootingFoe;
			for (EnemyType type : spawnPoints[spawnpointIndex]->possibleEnemiesTypes) {
				if (rand() % 101 < spawnPoints[spawnpointIndex]->enemyTypes[type]) {
					enemyType = type;
					break;
				}
			}
			sf::Vector2f pos = spawnPoints[spawnpointIndex]->position;
			pos.x += rand() % spawnPoints[spawnpointIndex]->size + spawnPoints[spawnpointIndex]->size / 2;
			SpawnEnemy(pos, enemyType);
			ResetClock();
		}
	}
}


void EnemySpawner::SpawnEnemy() {
	sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
	Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, 1, this->player);
	enemy->SetPosition(sf::Vector2f(128, 0));
	enemy->SetDirection(sf::Vector2f(0, 1));
	enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
	enemy->SetWindow(*window);
	rectangleEnemy->setSize(sf::Vector2f(64, 64));
	foeList->push_back(enemy);
}

void EnemySpawner::SpawnEnemy(int i) {
	sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
	Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, i+1, this->player);
	enemy->SetPosition(sf::Vector2f(64+64*i, 0));
	enemy->SetDirection(sf::Vector2f(0, 1));
	enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
	enemy->SetWindow(*window);
	rectangleEnemy->setSize(sf::Vector2f(64, 64));
	foeList->push_back(enemy);
}

void EnemySpawner::SpawnEnemy(sf::Vector2f position, EnemyType enemySpawnedType) {
	Entities::Foe* enemy = nullptr;
	switch (enemySpawnedType)
	{
	case LinearShootingFoe: {
		sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
		Entities::LinearFoe* linearFoe = new Entities::LinearShootingFoe(*rectangleEnemy, 50 + rand() % 200, this->player);
		linearFoe->SetPosition(sf::Vector2f(position.x, position.y));
		linearFoe->SetDirection(sf::Vector2f(0, 1));
		rectangleEnemy->setSize(sf::Vector2f(64, 64));
		enemy = linearFoe;
		break;
	}
	case NonLinearFoe: {
		sf::CircleShape* octogonalShape = new sf::CircleShape(8);
		Entities::NonLinearFoe* nonlinearFoe = new Entities::NonLinearFoe(*octogonalShape, 50 + rand() % 200, this->player);
		nonlinearFoe->SetPosition(sf::Vector2f(position.x, position.y));
		nonlinearFoe->SetDirection(sf::Vector2f(rand() % 2 == 0 ? -1 : 1, 1));
		octogonalShape->setRadius(48);
		enemy = nonlinearFoe;
		break;
	}
	default:
		break;
	}
	if (enemy != nullptr) {
		enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
		enemy->SetWindow(*window);
		foeList->push_back(enemy);
	}


}

