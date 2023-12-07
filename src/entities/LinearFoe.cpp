#include "LinearFoe.h"
#include "../UpgradeBoxSpawner.h"
#include "Player.h"

namespace Entities
{
	LinearFoe::LinearFoe(sf::Shape& shape, float speed, GameManager* pGameManager) : Foe(shape, speed, pGameManager) {
	}

	void LinearFoe::Update(float deltaTime) {
		this->Move(direction * speed, deltaTime);
		sf::Vector2f pos = shape.getPosition();
		if (pos.y > this->windowHeight + shape.getGlobalBounds().height) {
			player->GetHit(1);
		}
		if (IsCollidingWithPlayer()) {
			player->GetHit(1);
		}
	}

	void LinearFoe::SetDirection(sf::Vector2f direction) {
		this->direction = direction;
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