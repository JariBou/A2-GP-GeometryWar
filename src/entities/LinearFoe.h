#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Foe.h"
#include "Player.h"

namespace Entities

{

	class LinearFoe : public Foe {

	public:
		
		sf::Vector2f direction;

		LinearFoe(sf::Shape& shape, float speed, Player* player);

		virtual void Update(float deltaTime);
		virtual bool isDead();
		virtual void SetDirection(sf::Vector2f direction);
		virtual bool CheckLife();

		virtual void GetHit(float value);

	};
}