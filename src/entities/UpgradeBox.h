#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "Player.h"

namespace Entities
{
	enum UpgradeType {
		UpgradeSpeed,
		UpgradeBulletDamage,
		UpgradeBulletSpeed,
		UpgradeBulletNumber
	};
	class UpgradeBox : public DrawableEntity {
	public:
		UpgradeBox(sf::Shape& shape, Player& Player, int UpgradeTypeNb);
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