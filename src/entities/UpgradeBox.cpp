#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "UpgradeBox.h"
#include <random>
#include <iostream>

namespace Entities {

	UpgradeBox::UpgradeBox(sf::Shape& shape, Player& Player) : DrawableEntity(shape), player(Player) {
		speed = 200;
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
		

}



