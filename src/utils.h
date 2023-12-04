#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "entities/Bullet.h"
#include "entities/Foe.h"
#include "entities/UpgradeBox.h"

namespace Utils {

	sf::Vector2f NormalizeVector(sf::Vector2f vector);


	void CheckBulletListLife(std::vector<Entities::Bullet*>& bullets);
	int CheckFoeListLife(std::vector<Entities::Foe*>& foes);
	void CheckUpgradeListLife(std::vector<Entities::UpgradeBox*>& boxes);

	sf::String toString(int integers);
}
