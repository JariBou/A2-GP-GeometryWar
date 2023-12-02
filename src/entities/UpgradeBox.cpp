#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "UpgradeBox.h"
#include <random>
#include <iostream>

namespace Entities {

	UpgradeBox::UpgradeBox(sf::Shape& shape) : DrawableEntity(shape) {
		speed = 1000;
	}

	void UpgradeBox::Update(float deltaTime) {
		Move(sf::Vector2f(0,1), deltaTime*speed);

	}
		

}



