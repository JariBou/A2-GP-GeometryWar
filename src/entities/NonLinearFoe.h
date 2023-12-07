#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Foe.h"
#include "Player.h"

namespace Entities
{
	class Player;

	class NonLinearFoe : public Foe {

	public:

		sf::Vector2f direction;
		float clock = 0;
		float changeDirectionCooldown = 2;

		NonLinearFoe(sf::Shape& shape, float speed, Player* player);

		virtual void Update(float deltaTime);
		virtual bool isDead();
		virtual void SetDirection(sf::Vector2f direction);

		/// <summary>
		/// Function called when destroyed by PLAYER by "normal" means (i.e bullets)
		/// </summary>
		virtual void OnKilledByPlayer();

		/// <summary>
		/// Returns False if the entity should be removes
		/// </summary>
		/// <returns></returns>
		virtual void GetHit(float value);

		bool IsOutOfBounds();

	};
}
