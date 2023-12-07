#include "Foe.h"

namespace Entities {

	Foe::Foe(sf::Shape& shape, float speed, Player* player) : DrawableEntity(shape) {
		this->speed = speed;
		this->player = player;
	}
	
	void Foe::OnKilledByPlayer() {

	}

	void Foe::GetHit(float value) {
		this->health -= value;
		if (health <= 0) {
			//Die();
		}
	}

	bool Foe::IsCollidingWithPlayer() {
		auto selfRect = this->shape.getGlobalBounds();
		auto playerRect = player->shape.getGlobalBounds();

		bool shouldDestroy = selfRect.intersects(playerRect);
		return shouldDestroy;
	}

}