#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "UpgradeBox.h"
#include <random>
#include <iostream>

namespace Entities {

	UpgradeBox::UpgradeBox(sf::Shape& shape, Player& Player) : DrawableEntity(shape) {
		speed = 200;
		player = &Player;
	}

	void UpgradeBox::Update(float deltaTime) {
		Move(sf::Vector2f(0,1), deltaTime*speed);

	}

	bool UpgradeBox::isColliding() {
		auto selfRect = this->shape.getGlobalBounds();
		auto playerRect = player->shape.getGlobalBounds();

		if (selfRect.intersects(playerRect)) {
			return true;
		}
		return false;
	}
		

}



