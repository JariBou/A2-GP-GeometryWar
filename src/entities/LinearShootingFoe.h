#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "LinearFoe.h"
#include "Bullet.h"
#include "Player.h"

#include <vector>

namespace Entities

{

	class LinearShootingFoe : public LinearFoe {

	private:
		float shootingClock = 0;
		float shootingCooldown = 1.5;
		std::vector<Bullet*> bullets;

	public:

		LinearShootingFoe(sf::Shape& shape, float speed, Player* player);

		virtual void Update(float deltaTime);
		virtual void Draw(sf::RenderWindow& window);

	};
}