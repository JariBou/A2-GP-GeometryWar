#include "DrawableEntity.h"
#include "NonLinearFoe.h"
#include "../UpgradeBoxSpawner.h"

namespace Entities
{
	NonLinearFoe::NonLinearFoe(sf::Shape& shape, float speed, Player* player) : Foe(shape, speed, player) {
	}

	void NonLinearFoe::Update(float deltaTime) {
		this->Move(direction * speed, deltaTime);
		sf::Vector2f pos = shape.getPosition();
		if (pos.y > this->windowHeight + shape.getGlobalBounds().height) {
			this->health = 0;
			//Die();
		}
		clock += deltaTime;
		if (clock >= changeDirectionCooldown) {
			direction.x *= -1;
			clock = 0;
		}
	}

	bool NonLinearFoe::isDead() { return this->health <= 0; }

	void NonLinearFoe::SetDirection(sf::Vector2f direction) {
		this->direction = direction;
	}

	bool NonLinearFoe::CheckLife() {
		if (health <= 0) {
			return false;
		}
		return true;
	}

	void NonLinearFoe::OnKilledByPlayer() {
		player->GetBoxSpawner()->SpawnUpgradeBox(&shape);
	}

	void NonLinearFoe::GetHit(float value) {
		this->health -= value;
		if (health <= 0) {
			//Die();
		}
	}
}