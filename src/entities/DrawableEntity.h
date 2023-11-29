#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

namespace Entities
{

	class DrawableEntity {

		public:
			DrawableEntity(sf::Shape& shape);

			virtual ~DrawableEntity() = default;

			virtual void Draw(sf::RenderWindow& window);

			virtual void Move(sf::Vector2f vectorMove);

			virtual void SetPosition(sf::Vector2f pos);

			virtual void SetColor(sf::Color color, sf::Color color2);
			virtual void SetColor(sf::Color color);


			sf::Shape& shape;
	};
}

