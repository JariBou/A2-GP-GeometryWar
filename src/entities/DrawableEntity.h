#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

namespace Entities
{

	class DrawableEntity {

	public:

		sf::Shape& shape;
		ShapeType shapeType = 0;

		DrawableEntity(sf::Shape& shape) : shape(shape) {
		
		}

		virtual ~DrawableEntity() = default;

		virtual void Draw(sf::RenderWindow& window) {
			window.draw(this->shape);
		}

		virtual void Move(sf::Vector2f vectorMove){
			sf::Vector2f pos = shape.getPosition();
			pos += vectorMove;
			shape.setPosition(pos);
		}

		virtual void SetPosition(sf::Vector2f pos) {
			shape.setPosition(pos);
		}

		virtual void SetColor(sf::Color color) {
			switch (shapeType)
			{
				case ShapeType::FILLED:
					shape.setFillColor(color);
					shape.setOutlineColor(sf::Color::Transparent);
					break;
				case ShapeType::OUTLINED:
					shape.setOutlineColor(color);
					shape.setFillColor(sf::Color::Transparent);
					break;
				default:
					break;
			}
		}

		virtual void SetShapeType(ShapeType type) {
			shapeType = type;
		}
	};

}
enum class ShapeType
{
	FILLED = 0,
	OUTLINED = 1,
};

