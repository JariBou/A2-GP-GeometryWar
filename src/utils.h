#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Entities {
	class Bullet;
	class Foe;
	class UpgradeBox;
}

namespace Utils {

	sf::Vector2f NormalizeVector(sf::Vector2f vector);


	void CheckBulletListLife(std::vector<Entities::Bullet*>& bullets);
	int CheckFoeListLife(std::vector<Entities::Foe*>& foes);
	void CheckUpgradeListLife(std::vector<Entities::UpgradeBox*>& boxes);

	sf::String toString(int integers);
}
