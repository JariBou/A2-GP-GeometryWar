#include "NonLinearFoe.h"
#include "../UpgradeBoxSpawner.h"
#include "Player.h"

namespace Entities
{
	NonLinearFoe::NonLinearFoe(sf::Shape& shape, float speed, Player* player) : Foe(shape, speed, player) {
	}

	void NonLinearFoe::Update(float deltaTime) {
		this->Move(direction * speed, deltaTime);
		sf::Vector2f pos = shape.getPosition();
		if (pos.y > this->windowHeight + shape.getGlobalBounds().height) {
			player->GetHit(1);
		}
		if (IsCollidingWithPlayer()) {
			player->GetHit(1);
		}
		clock += deltaTime;
		if (clock >= changeDirectionCooldown || pos.x < 0 || pos.x>windowWidth) {
			direction.x *= -1;
			clock = 0;
		}
	}

	bool NonLinearFoe::isDead() {
		return this->health <= 0;

	}

	void NonLinearFoe::SetDirection(sf::Vector2f direction) {
		this->direction = direction;
	}

	void NonLinearFoe::OnKilledByPlayer() {
		player->GetBoxSpawner()->SpawnUpgradeBox(&shape);
	}

	void NonLinearFoe::GetHit(float value) {
		this->health -= value;
	}

	//TODO
	bool NonLinearFoe::IsOutOfBounds() {
		if (shape.getPosition().y > this->windowHeight + shape.getGlobalBounds().height) {
			return true;
		}
		return false;
	}
}