#include "src/entities/DrawableEntity.h"
#include "src/entities/LinearFoe.h"

namespace Entities
{

	LinearFoe::LinearFoe(sf::Shape& shape, float speed) : DrawableEntity(shape) {
		this->speed = speed;
		this->health = 20;
	}

	void LinearFoe::Update() {
		this->Move(direction * speed);
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

	void LinearFoe::Hit(float value) {
		this->health -= value;
		if (health <= 0) {
			//Die();
		}
	}
}