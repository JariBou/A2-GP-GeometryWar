#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Player.h"
#include <iostream>

namespace Entities {

	Bullet::Bullet(sf::Shape& shape, Player& Joueur) : DrawableEntity(shape), player(Joueur) {
		speed = 300.0f;
		std::cout << "Bullet created with Player instance" << std::endl;
		
	}

	void Bullet::MoveBullet(float deltaTime) {
		Move(sf::Vector2f(0.0, -1.0) * speed * deltaTime);
		if (shape.getPosition().y < 0 - shape.getLocalBounds().height) {
			std::vector<Bullet*>::iterator it = player.GetBullets().begin();
			for (Bullet* bullet : player.GetBullets()) {
				if (bullet == this) {
					player.GetBullets().erase(it);
					delete bullet;
					std::cout << "Bullet deleted" << std::endl;
					break;
				}
				it++;	
				
			}
		}
	}

	void Bullet::Udapte(float deltaTime) {

	}	


}