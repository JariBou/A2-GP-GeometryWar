#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"

namespace Entities {
	class Bullet : public DrawableEntity {
		public:
			int damage;
			float speed;
			Bullet(sf::Shape& shape);
			Bullet(sf::Shape& shape, Player player);
			virtual ~Bullet() = default;
			virtual void MoveBullet(float deltaTime);
			virtual void Udapte(float deltaTime);
	};
}