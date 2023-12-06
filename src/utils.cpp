#include "utils.h"
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;


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
				/*std::cout << "Bullet deleted" << std::endl;*/
			}
		}
	}

	int CheckFoeListLife(std::vector<Entities::Foe*>& foes) {
		int killedFoe = 0;
		auto foeVectorIterator = foes.begin();
		while (foeVectorIterator != foes.end()) {
			if ((*foeVectorIterator)->CheckLife()) {
				foeVectorIterator++;
			}
			else {
				if ((*foeVectorIterator)->health <= 0) {
					(*foeVectorIterator)->OnKilledByPlayer();
				}
				foeVectorIterator = foes.erase(foeVectorIterator);
				killedFoe++;
				std::cout << "Foe deleted" << std::endl;
			}
		}
		return killedFoe;
	}

	void CheckUpgradeListLife(std::vector<Entities::UpgradeBox*>& boxes) {
		auto upgradeVectorIterator = boxes.begin();
		while (upgradeVectorIterator != boxes.end()) {
			if ((*upgradeVectorIterator)->CheckLife()) {
				upgradeVectorIterator++;
			}
			else {
				upgradeVectorIterator = boxes.erase(upgradeVectorIterator);
				std::cout << "Upgrade deleted" << std::endl;
			}
		}
	}

	// Omg, can't stress how much I HATE this nonsense of "gngngn no you can't use parent class as parameter"
	void CheckEntityListLife(std::vector<Entities::DrawableEntity*>* boxes) {
		auto upgradeVectorIterator = boxes->begin();
		while (upgradeVectorIterator != boxes->end()) {
			if ((*upgradeVectorIterator)->CheckLife()) {
				upgradeVectorIterator++;
			}
			else {
				upgradeVectorIterator = boxes->erase(upgradeVectorIterator);
				std::cout << "Upgrade deleted" << std::endl;
			}
		}
	}

	sf::String toString(int integer)
	{
		std::ostringstream os;
		os << integer;
		return os.str();
	}

}