#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"

namespace Entities

{

	class Player : public DrawableEntity {

	public:

		int lives;

		Player(sf::Shape& shape) : DrawableEntity(shape) {
			lives = 3;
		}



	};
}