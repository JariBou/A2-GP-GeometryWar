#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"

namespace Entities
{
	class UpgradeBox : public DrawableEntity {
	public:
		UpgradeBox(sf::Shape& shape);
		~UpgradeBox() = default;
		virtual void Update(float deltaTime);
	private:
		int speed = 200;
	};

}