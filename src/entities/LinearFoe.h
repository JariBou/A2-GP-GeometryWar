#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"

namespace Entities

{

	class LinearFoe : public DrawableEntity {

	public:
		
		int health = 20;
		sf::Vector2f direction;
		float speed = 5;

		LinearFoe(sf::Shape& shape, float speed);

		void Update();
		bool isDead();
		void SetDirection(sf::Vector2f direction);

		void Hit(float value);






	};
}