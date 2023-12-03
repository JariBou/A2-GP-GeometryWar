#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Player.h"
#include "Foe.h"
#include "../EnemySpawner.h"
#include <iostream>

namespace Entities {

	Bullet::Bullet(sf::Shape& shape, Player& Joueur) : DrawableEntity(shape), player(Joueur) {
		speed = 300.0f;
		damage = 1;
		std::cout << "Bullet created" << std::endl;
		std::cout << shape.getPosition().y << std::endl;
	}

	Bullet::Bullet(sf::Shape& shape, Player& Joueur, int damage, float speed, sf::Vector2f Direction, int WindowWidth) : DrawableEntity(shape), player(Joueur) {
		this->damage = damage;
		this->speed = speed;
		//std::cout << "Bullet created" << std::endl;
		//std::cout << shape.getPosition().y << std::endl;
		direction = Direction;
		windowWidth = WindowWidth;
	}

	bool Bullet::MoveBullet(float deltaTime) {
		Move(sf::Vector2f(direction) * speed, deltaTime);
		return true;
	}

	void Bullet::Update(float deltaTime) {
		MoveBullet(deltaTime);
		CheckHit();
	}	

	bool Bullet::CheckLife() {
		if (this->shouldDestroy) return false;

		float windowWidth = player.windowWidth;
		float windowHeight = player.windowHeight;

		if (shape.getPosition().x < 0 - shape.getLocalBounds().width || shape.getPosition().y < 0 - shape.getLocalBounds().height 
			|| shape.getPosition().x > windowWidth + shape.getLocalBounds().width || shape.getPosition().y > windowHeight + shape.getLocalBounds().height){
			return false;
		}
		return true;
	}

	bool Bullet::CheckHit() {

		auto selfRect = this->shape.getGlobalBounds();

		if (shotByPlayer) {
			EnemySpawner* spawner = this->player.GetSpawner();

			for (Foe* foe : *(spawner->GetFoes())) {

				auto enemyRect = foe->shape.getGlobalBounds();

				if (enemyRect.intersects(selfRect)) {
					foe->GetHit(this->damage);
					shouldDestroy = true;
					return true;
				}

			}
		}
		else {
			if (player.shape.getGlobalBounds().intersects(selfRect)) {
				player.GetHit(this->damage);
				shouldDestroy = true;
				return true;
			}
		}
		
		return false;
	}


}