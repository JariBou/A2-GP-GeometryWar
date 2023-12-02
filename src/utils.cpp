#include "utils.h"
#include <cmath>
#include <iostream>


namespace Utils {

	sf::Vector2f NormalizeVector(sf::Vector2f vector) {
		float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude == 0) {
			return sf::Vector2f(0, 0);
		}

		return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);

	}

	void CheckBulletListLife(std::vector<Entities::Bullet*>& bullets) {
		auto bulletVectorIterator = bullets.begin();
		while (bulletVectorIterator != bullets.end()) {
			if ((*bulletVectorIterator)->CheckLife()) {
				bulletVectorIterator++;
			}
			else {
				bulletVectorIterator = bullets.erase(bulletVectorIterator);
				std::cout << "Bullet deleted" << std::endl;
			}
		}
	}

}