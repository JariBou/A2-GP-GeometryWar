#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "UpgradeBoxSpawner.h"
#include "entities/UpgradeBox.h"


UpgradeBoxSpawner::UpgradeBoxSpawner(std::vector<Entities::UpgradeBox*>& UpgradeBoxList, int WindowWidth) {
	upgradeBoxList = UpgradeBoxList;
	windowWidth = WindowWidth;
}

void UpgradeBoxSpawner::SpawnUpgradeBox() {
	
	sf::RectangleShape* rectangleUpgradeBox = new sf::RectangleShape(sf::Vector2f(50, 50));
	Entities::UpgradeBox* UpgradeBox = new Entities::UpgradeBox(*rectangleUpgradeBox);
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> xDist(0, windowWidth - UpgradeBox->shape.getLocalBounds().width);
	int random_number = xDist(rng);
	std::cout << "Nombre aléatoire : " << random_number << std::endl;
	UpgradeBox->SetPosition(sf::Vector2f(0, ));
	UpgradeBox->SetColor(sf::Color::Red);
	upgradeBoxList.push_back(UpgradeBox);
}

std::vector<Entities::UpgradeBox*>& UpgradeBoxSpawner::GetUpgradeBoxList() {
	return upgradeBoxList;
}
