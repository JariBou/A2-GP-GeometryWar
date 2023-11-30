#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"

namespace Entities {
	class Bullet : public DrawableEntity {
		public:
			int damage;
			Bullet();
			virtual ~Bullet() = default;
			virtual void MoveBullet();
			virtual void Udapte(float deltaTime);

	};
}