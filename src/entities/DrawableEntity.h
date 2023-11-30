#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

namespace Entities
{

	enum class ShapeType   
	{
		FILLED = 0,
		OUTLINED = 1,
	};


	class DrawableEntity {

		public:
			DrawableEntity(sf::Shape& shape);

			virtual ~DrawableEntity() = default;

			virtual void Draw(sf::RenderWindow& window);

			virtual void Move(sf::Vector2f vectorMove);

			virtual void SetPosition(sf::Vector2f pos);

			virtual void SetColor(sf::Color color);

			virtual void GetWindowwSize(sf::RenderWindow& window);

			sf::Shape& shape;
			int windowWidth;
			int windowHeight;

	};
}

