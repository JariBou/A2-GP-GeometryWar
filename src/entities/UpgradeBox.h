#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "Player.h"

namespace Entities
{
	class UpgradeBox : public DrawableEntity {
	public:
		UpgradeBox(sf::Shape& shape, Player& Player);
		~UpgradeBox() = default;
		virtual void Update(float deltaTime);
		virtual bool isColliding();

	private:
		int speed = 200;
		Player* player;
	};

}