#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

namespace Entities
{

	class DrawableEntity {

	public:

		sf::Shape& shape;

		DrawableEntity(sf::Shape& shape) : shape(shape) {

		}

		virtual ~DrawableEntity() = default;

		virtual void Draw(sf::RenderWindow& window) {
			window.draw(this->shape);
		}
	};


	class Player : public DrawableEntity {

	public:

		int lives = 3;

		Player(sf::Shape& shape) : DrawableEntity(shape) {
			
		}



	};
}
