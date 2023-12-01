#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Foe.h"

namespace Entities

{

	class LinearFoe : public Foe {

	public:
		
		sf::Vector2f direction;

		LinearFoe(sf::Shape& shape, float speed);

		void Update(float deltaTime);
		bool isDead();
		void SetDirection(sf::Vector2f direction);
		bool CheckLife();

		void GetHit(float value);

	};
}