#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "src/entities/Bullet.h"

namespace Entities {


	Bullet::Bullet() : DrawableEntity(shape) {
		shape = sf::RectangleShape(sf::Vector2f(20, 128));
	}

	void Bullet::MoveBullet() {

	}

	void Bullet::Udapte(float deltaTime) {

	}	
}