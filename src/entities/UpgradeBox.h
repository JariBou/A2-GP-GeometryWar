#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "../enum.h"


namespace Entities
{
	class Player;
	
	class UpgradeBox : public DrawableEntity {
	public:
		UpgradeBox(sf::Shape& shape, GameManager* pGameManager, int UpgradeTypeNb);
		~UpgradeBox() = default;
		virtual void Update(float deltaTime);
		virtual bool IsColliding();
		virtual bool CheckLife();
		virtual UpgradeType GetUpgradeType();
		UpgradeType upgradeType;

	private:
		bool shouldDestroy = false;
		int speed = 200;
		Player& player;
	};


}