#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "UpgradeBoxSpawner.h"
#include "entities/UpgradeBox.h"
#include "entities/Player.h"
#include "GameManager.h"

UpgradeBoxSpawner::UpgradeBoxSpawner(std::vector<Entities::UpgradeBox*>& UpgradeBoxList, int WindowWidth, GameManager* pGameManager) : gameManager(pGameManager) {
	upgradeBoxList = UpgradeBoxList;
	windowWidth = WindowWidth;
	gameManager->SetUpgradeBoxSpawner(this);
	player = gameManager->GetPlayer();
}

void UpgradeBoxSpawner::SpawnUpgradeBox(sf::Shape* shape)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> type(0, 3);
	int chance_to_spawn = type(rng);
	int random_type = type(rng);
	float x;
	float y;
	if (chance_to_spawn < 2) {
		switch (random_type)
		{
			case 0:
				//Speed
				if (player->movementSpeedLevel < 12) {
					sf::CircleShape* triangleUpgradeBox = new sf::CircleShape(50, 3);
					Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*triangleUpgradeBox, *player, random_type);
					auto shapeRect = shape->getGlobalBounds();
					x = shapeRect.left + shapeRect.width / 2 - UpgradeBox->shape.getLocalBounds().width / 2;
					y = shapeRect.top;
					UpgradeBox->SetPosition(sf::Vector2f(x, y - (UpgradeBox->shape.getLocalBounds().height / 2)));
					UpgradeBox->SetColor(sf::Color::Transparent, sf::Color::Blue);
					upgradeBoxList.push_back(UpgradeBox);
				}
				break;
			case 1:
				//Bullet Speed
				if (player->bulletSpeedLevel < 8) {
					sf::CircleShape* octogonUpgradeBox = new sf::CircleShape(50, 8);
					Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*octogonUpgradeBox, *player, random_type);
					auto shapeRect = shape->getGlobalBounds();
					x = shapeRect.left + shapeRect.width / 2 - UpgradeBox->shape.getLocalBounds().width / 2;
					y = shapeRect.top;
					UpgradeBox->SetPosition(sf::Vector2f(x, y - (UpgradeBox->shape.getLocalBounds().height / 2)));
					UpgradeBox->SetColor(sf::Color::Transparent, sf::Color::Blue);
					upgradeBoxList.push_back(UpgradeBox);
				}
				break;
			case 2:
				//Bullet Damage
				if (player->bulletDamageLevel < 10) {
					sf::RectangleShape* rectangleUpgradeBox = new sf::RectangleShape(sf::Vector2f(50, 50));
					Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*rectangleUpgradeBox, *player, random_type);
					auto shapeRect = shape->getGlobalBounds();
					x = shapeRect.left + shapeRect.width / 2 - UpgradeBox->shape.getLocalBounds().width / 2;
					y = shapeRect.top;
					UpgradeBox->SetPosition(sf::Vector2f(x, y - (UpgradeBox->shape.getLocalBounds().height / 2)));
					UpgradeBox->SetColor(sf::Color::Transparent, sf::Color::Magenta);
					upgradeBoxList.push_back(UpgradeBox);
				}
				break;
			case 3:
				//Bullet Number
				if (player->bulletNumberLevel < 4) {
					sf::CircleShape* circleUpgradeBox = new sf::CircleShape(50);
					Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*circleUpgradeBox, *player, random_type);
					auto shapeRect = shape->getGlobalBounds();
					x = shapeRect.left + shapeRect.width / 2 - UpgradeBox->shape.getLocalBounds().width / 2;
					y = shapeRect.top;
					UpgradeBox->SetPosition(sf::Vector2f(x, y - (UpgradeBox->shape.getLocalBounds().height / 2)));
					UpgradeBox->SetColor(sf::Color::Transparent, sf::Color::Green);
					upgradeBoxList.push_back(UpgradeBox);
				}
				break;
			}
	}
	
	//sf::RectangleShape* rectangleUpgradeBox = new sf::RectangleShape(sf::Vector2f(50, 50));
	//Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*rectangleUpgradeBox, *player, random_type);
}

//void UpgradeBoxSpawner::TrySpawning(float deltaTime) {
//	spawnTimer += deltaTime;
//
//	if (spawnTimer >= spawnCooldown) {
//		SpawnUpgradeBox();
//		std::string boxUpgradeType = "";
//		switch (upgradeBoxList.back()->upgradeType)
//		{
//			case 0:
//				boxUpgradeType = "Speed";
//				break;
//			case 1:
//				boxUpgradeType = "Bullet Damage";
//				break;
//			case 2:
//				boxUpgradeType = "Bullet Speed";
//				break;
//			case 3:
//				boxUpgradeType = "Bullet Number";
//				break;
//		}
//		std::cout << "Upgrade Box spawned with type : "<< boxUpgradeType << std::endl;
//		spawnTimer = 0;
//	}
//}

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
			player->UpgradeLevel(box->GetUpgradeType());
		}
	}
}


