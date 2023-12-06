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

//void UpgradeBoxSpawner::SpawnUpgradeBox() {
//	std::mt19937 rng(std::random_device{}());
//	std::uniform_int_distribution<int> type(0, 3);
//	int random_type = type(rng);
//	switch (random_type)
//	{
//		case 0:
//			//Speed
//			{
//				sf::CircleShape* triangleUpgradeBox = new sf::CircleShape(50, 3);
//				Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*triangleUpgradeBox, *player, random_type);
//				std::mt19937 rng(std::random_device{}());
//				std::uniform_int_distribution<int> xDist(0, windowWidth - UpgradeBox->shape.getLocalBounds().width);
//				int random_number = xDist(rng);
//				std::cout << "Nombre aleatoire : " << random_number << std::endl;
//				UpgradeBox->SetPosition(sf::Vector2f(random_number, -UpgradeBox->shape.getLocalBounds().height));
//				UpgradeBox->SetColor(sf::Color::Transparent, sf::Color::Blue);
//				upgradeBoxList.push_back(UpgradeBox);
//				break;
//			}
//		case 1:
//			//Bullet Speed
//			{
//				sf::CircleShape* octogonUpgradeBox = new sf::CircleShape(50, 3);
//				Entities::UpgradeBox* UpgradeBox1 = new Entities::UpgradeBox(*octogonUpgradeBox, *player, random_type);
//				std::mt19937 rng(std::random_device{}());
//				std::uniform_int_distribution<int> xDist(0, windowWidth - UpgradeBox1->shape.getLocalBounds().width);
//				int random_number = xDist(rng);
//				std::cout << "Nombre aleatoire : " << random_number << std::endl;
//				UpgradeBox1->SetPosition(sf::Vector2f(random_number, -UpgradeBox1->shape.getLocalBounds().height));
//				UpgradeBox1->SetColor(sf::Color::Transparent, sf::Color::Blue);
//				upgradeBoxList.push_back(UpgradeBox1);
//				break;
//			}
//		case 2:
//			//Bullet Damage
//			{
//				sf::RectangleShape * rectangleUpgradeBox = new sf::RectangleShape(sf::Vector2f(50, 50));
//				Entities::UpgradeBox* UpgradeBox2 = new Entities::UpgradeBox(*rectangleUpgradeBox, *player, random_type);
//				std::mt19937 rng(std::random_device{}());
//				std::uniform_int_distribution<int> xDist(0, windowWidth - UpgradeBox2->shape.getLocalBounds().width);
//				int random_number = xDist(rng);
//				std::cout << "Nombre aleatoire : " << random_number << std::endl;
//				UpgradeBox2->SetPosition(sf::Vector2f(random_number, -UpgradeBox2->shape.getLocalBounds().height));
//				UpgradeBox2->SetColor(sf::Color::Transparent, sf::Color::Magenta);
//				upgradeBoxList.push_back(UpgradeBox2);
//				break;
//			}
//		case 3:
//			//Bullet Number
//			{
//				sf::CircleShape* circleUpgradeBox = new sf::CircleShape(50);
//				Entities::UpgradeBox* UpgradeBox3 = new Entities::UpgradeBox(*circleUpgradeBox, *player, random_type);
//				std::mt19937 rng(std::random_device{}());
//				std::uniform_int_distribution<int> xDist(0, windowWidth - UpgradeBox3->shape.getLocalBounds().width);
//				int random_number = xDist(rng);
//				std::cout << "Nombre aleatoire : " << random_number << std::endl;
//				UpgradeBox3->SetPosition(sf::Vector2f(random_number, -UpgradeBox3->shape.getLocalBounds().height));
//				UpgradeBox3->SetColor(sf::Color::Transparent, sf::Color::Green);
//				upgradeBoxList.push_back(UpgradeBox3);
//				break;
//			}
//	}
//
//}

void UpgradeBoxSpawner::SpawnUpgradeBox(sf::Shape* shape)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> type(0, 3);
	int chance_to_spawn = type(rng);
	int random_type = type(rng);
	float x;
	float y;
	if (chance_to_spawn <= 1) {
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


