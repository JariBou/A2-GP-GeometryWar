#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "Bullet.h"

namespace Entities
{
	constexpr float cubeSpeed = 500.f;

	class Player : public DrawableEntity {

		public:

			int lives = 3;

			Player(sf::Shape& shape);
			virtual ~Player() = default;
			virtual void MovePlayer();
			virtual void ShootPlayer();
			virtual std::vector<Bullet> GetBullets();
			float playerWidth;
			float playerHeight;

		private:
			std::vector<Bullet> bullets;
			bool isMouseClickedLastFrame;
	
	};
}