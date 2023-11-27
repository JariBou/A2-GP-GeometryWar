#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

namespace Entities
{
	class Player : public DrawableEntity {

	public:

		int lives = 3;

		Player(sf::Shape& shape) : DrawableEntity(shape) {

		}



	};
}