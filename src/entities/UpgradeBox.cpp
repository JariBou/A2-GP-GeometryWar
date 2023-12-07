#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include <iostream>
#include <random>
#include "UpgradeBox.h"
#include "../enum.h"
#include "Player.h"

namespace Entities {

	UpgradeBox::UpgradeBox(sf::Shape& shape, Player& Player, int UpgradeTypeNb) : DrawableEntity(shape), player(Player) {
		speed = 200;
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> type(0, 3);
		int random_number = type(rng);
		upgradeType = UpgradeType(UpgradeTypeNb);
	}

	void UpgradeBox::Update(float deltaTime) {
		Move(sf::Vector2f(0,1), deltaTime*speed);
	}

	bool UpgradeBox::IsColliding() {
		auto selfRect = this->shape.getGlobalBounds();
		auto playerRect = player.shape.getGlobalBounds();

		shouldDestroy = selfRect.intersects(playerRect);
		return shouldDestroy;
	}

	bool UpgradeBox::CheckLife() {

		if (this->shouldDestroy) return false;

		float windowWidth = player.windowWidth;
		float windowHeight = player.windowHeight;

		if (shape.getPosition().x < 0 - shape.getLocalBounds().width || shape.getPosition().y < 0 - shape.getLocalBounds().height
			|| shape.getPosition().x > windowWidth + shape.getLocalBounds().width || shape.getPosition().y > windowHeight + shape.getLocalBounds().height) {
			return false;
		}
		return true;

	}

	UpgradeType UpgradeBox::GetUpgradeType() {
		return upgradeType;
	}
		

}



