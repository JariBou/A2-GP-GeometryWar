#include "DrawableEntity.h"
#include "LinearFoe.h"

namespace Entities
{

	Foe::Foe(sf::Shape& shape, float speed) : DrawableEntity(shape) {
		this->speed = speed;
		this->health = 20;
	}

	bool Foe::isDead() { return this->health <= 0; }

	void Foe::GetHit(float value) {
		this->health -= value;
		if (health <= 0) {
			//Die();
		}
	}
}