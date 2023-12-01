#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(std::vector<Entities::Foe*>* foeList, sf::RenderWindow* window) {
	this->foeList = foeList;
	this->window = window;
}


void EnemySpawner::SpawnEnemy() {
	sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
	Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, 1);
	enemy->SetPosition(sf::Vector2f(128, 0));
	enemy->SetDirection(sf::Vector2f(0, 1));
	enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
	enemy->SetWindow(*window);
	rectangleEnemy->setSize(sf::Vector2f(64, 64));
	foeList->push_back(enemy);
}

void EnemySpawner::SpawnEnemy(int i) {
	sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
	Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, i+1);
	enemy->SetPosition(sf::Vector2f(64+64*i, 0));
	enemy->SetDirection(sf::Vector2f(0, 1));
	enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
	enemy->SetWindow(*window);
	rectangleEnemy->setSize(sf::Vector2f(64, 64));
	foeList->push_back(enemy);
}

void EnemySpawner::SpawnEnemy(sf::Vector2f position) {
	sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
	Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, 1);
	enemy->SetPosition(sf::Vector2f(position.x, position.y));
	enemy->SetDirection(sf::Vector2f(0, 1));
	enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
	enemy->SetWindow(*window);
	rectangleEnemy->setSize(sf::Vector2f(64, 64));
	foeList->push_back(enemy);
}

