#include "src/entities/DrawableEntity.h"
#include "src/entities/Entites.h"

namespace Entities
{
	DrawableEntity::DrawableEntity(sf::Shape& shape) : shape(shape), shapeType(ShapeType::FILLED) {}

	void DrawableEntity::Draw(sf::RenderWindow& window) {
		window.draw(this->shape);
	}

	void DrawableEntity::Move(sf::Vector2f vectorMove) {
		sf::Vector2f pos = shape.getPosition();
		pos += vectorMove;
		shape.setPosition(pos);
	}

	void DrawableEntity::SetPosition(sf::Vector2f pos) {
		shape.setPosition(pos);
	}

	void DrawableEntity::SetColor(sf::Color color) {
		switch (shapeType)
		{
		case ShapeType::FILLED:
			shape.setFillColor(color);
			shape.setOutlineColor(sf::Color::Transparent);
			break;
		case ShapeType::OUTLINED:
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineColor(color);
			break;
		default:
			break;
		}
	}

	void DrawableEntity::SetShapeType(ShapeType type) {
		shapeType = type;
	}
}
