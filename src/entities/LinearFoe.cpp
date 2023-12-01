#include "DrawableEntity.h"
#include "LinearFoe.h"

namespace Entities
{

	LinearFoe::LinearFoe(sf::Shape& shape, float speed) : Foe(shape, speed) {
	}

	void LinearFoe::Update(float deltaTime) {
		this->Move(direction * speed, deltaTime);
		sf::Vector2f pos = shape.getPosition();
		if (pos.y > 720) {
			this->health = 0;
			//Die();
		}
	}

	bool LinearFoe::isDead() { return this->health <= 0; }

	void LinearFoe::SetDirection(sf::Vector2f direction) {
		this->direction = direction;
	}

	bool LinearFoe::CheckLife() {
		if (health <= 0) {
			return false;
		}
		return true;
	}


	void LinearFoe::GetHit(float value) {
		this->health -= value;
		if (health <= 0) {
			//Die();
		}
	}
}