#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "UpgradeBoxSpawner.h"
#include "entities/UpgradeBox.h"


UpgradeBoxSpawner::UpgradeBoxSpawner(std::vector<Entities::UpgradeBox*>& UpgradeBoxList, int WindowWidth, Entities::Player& Player) {
	upgradeBoxList = UpgradeBoxList;
	windowWidth = WindowWidth;
	player = &Player;
}

void UpgradeBoxSpawner::SpawnUpgradeBox() {
	
	sf::RectangleShape* rectangleUpgradeBox = new sf::RectangleShape(sf::Vector2f(50, 50));
	Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*rectangleUpgradeBox, *player);
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> xDist(0, windowWidth - UpgradeBox->shape.getLocalBounds().width);
	int random_number = xDist(rng);
	std::cout << "Nombre aleatoire : " << random_number << std::endl;
	UpgradeBox->SetPosition(sf::Vector2f(random_number, -UpgradeBox->shape.getLocalBounds().height));
	UpgradeBox->SetColor(sf::Color::Transparent, sf::Color::Green);
	upgradeBoxList.push_back(UpgradeBox);
}

void UpgradeBoxSpawner::SpawnUpgradeBox(sf::Shape* shape)
{
	sf::RectangleShape* rectangleUpgradeBox = new sf::RectangleShape(sf::Vector2f(50, 50));
	Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*rectangleUpgradeBox, *player);

	auto shapeRect = shape->getGlobalBounds();

	float x = shapeRect.left + shapeRect.width / 2 - rectangleUpgradeBox->getLocalBounds().width/2;
	float y = shapeRect.top;

	UpgradeBox->SetPosition(sf::Vector2f(x, y - (rectangleUpgradeBox->getLocalBounds().height / 2)));
	UpgradeBox->SetColor(sf::Color::Transparent, sf::Color::Green);
	upgradeBoxList.push_back(UpgradeBox);
}

void UpgradeBoxSpawner::TrySpawning(float deltaTime) {
	spawnTimer += deltaTime;

	if (spawnTimer >= spawnCooldown) {
		SpawnUpgradeBox();
		std::cout << "Upgrade Box spawned" << std::endl;
		spawnTimer = 0;
	}
}

std::vector<Entities::UpgradeBox*>& UpgradeBoxSpawner::GetUpgradeBoxList() {
	return upgradeBoxList;
}

std::vector<Entities::DrawableEntity*>& UpgradeBoxSpawner::GetUpgradeBoxEntities()
{
	std::vector<Entities::DrawableEntity*> vec;
	for (Entities::UpgradeBox* bullet : upgradeBoxList) {
		vec.push_back(bullet);
	}
	return vec;
}

void UpgradeBoxSpawner::Update(float deltaTime) {
	for (Entities::UpgradeBox* box : upgradeBoxList) {
		box->Update(deltaTime);
		if (box->IsColliding()) {
			player->UpgradeLevel();
		}
	}
}


