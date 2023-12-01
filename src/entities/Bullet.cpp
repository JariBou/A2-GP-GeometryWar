#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Player.h"
#include <iostream>

namespace Entities {

	Bullet::Bullet(sf::Shape& shape, Player& Joueur) : DrawableEntity(shape), player(Joueur) {
		speed = 300.0f;
		damage = 1;
		std::cout << "Bullet created" << std::endl;
		std::cout << shape.getPosition().y << std::endl;
	}

	Bullet::Bullet(sf::Shape& shape, Player& Joueur, int damage, float speed) : DrawableEntity(shape), player(Joueur) {
		this->damage = damage;
		this->speed = speed;
		std::cout << "Bullet created" << std::endl;
		std::cout << shape.getPosition().y << std::endl;
	}

	bool Bullet::MoveBullet(float deltaTime) {
		Move(sf::Vector2f(0.0, -1.0) * speed, deltaTime);

		return true;
	}

	void Bullet::Udapte(float deltaTime) {

	}	

	bool Bullet::CheckLife() {
		if (shape.getPosition().y < 0 - shape.getLocalBounds().height) {
			return true;
		}
		return true;
	}


}