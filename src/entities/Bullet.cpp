#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

namespace Entities {

	Bullet::Bullet(sf::Shape& shape) : DrawableEntity(shape) {
		speed = 300.0f;
		std::cout << "Bullet created" << std::endl;
		std::cout << shape.getPosition().y << std::endl;
	}

	void Bullet::MoveBullet(float deltaTime) {
		Move(sf::Vector2f(0.0, -1.0) * speed * deltaTime);
	}

	void Bullet::Udapte(float deltaTime) {

	}	
}