#include "DrawableEntity.h"
#include "LinearFoe.h"
#include "../UpgradeBoxSpawner.h"

namespace Entities
{
	LinearFoe::LinearFoe(sf::Shape& shape, float speed, Player* player) : Foe(shape, speed, player) {
	}

	void LinearFoe::Update(float deltaTime) {
		this->Move(direction * speed, deltaTime);
		sf::Vector2f pos = shape.getPosition();
		if (pos.y > this->windowHeight + shape.getGlobalBounds().height) {
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

	void LinearFoe::OnKilledByPlayer() {
		player->GetBoxSpawner()->SpawnUpgradeBox(&shape);
	}

	void LinearFoe::GetHit(float value) {
		this->health -= value;
		if (health <= 0) {
			//Die();
		}
	}
}