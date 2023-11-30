#include "src/entities/DrawableEntity.h"
#include "src/entities/Entites.h"

namespace Entities
{
	DrawableEntity::DrawableEntity(sf::Shape& shape) : shape(shape){}

	void DrawableEntity::Draw(sf::RenderWindow& Window) {
		Window.draw(this->shape);
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
		shape.setFillColor(color);
	}

	void DrawableEntity::GetWindowwSize(sf::RenderWindow& window)
	{
		windowHeight = window.getSize().y;
		windowWidth = window.getSize().x;
		
	}

}
