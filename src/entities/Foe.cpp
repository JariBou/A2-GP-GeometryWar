#include "Foe.h"
#include "Player.h"

namespace Entities {

	Foe::Foe(sf::Shape& shape, float speed, Player* player) : DrawableEntity(shape) {
		this->speed = speed;
		this->player = player;
	}
	
	
	bool Foe::isDead() {
		return this->health <= 0;
	}

	void Foe::OnDestroyed()
	{
		// TODO
	}

	void Foe::GetHit(float value) {
		this->health -= value;
	}

	bool Foe::CheckLife() {
		if (health <= 0) {
			return false;
		}
		return !(IsCollidingWithPlayer() || IsOutOfBounds());
	}

	bool Foe::IsCollidingWithPlayer() {
		auto selfRect = this->shape.getGlobalBounds();
		auto playerRect = player->shape.getGlobalBounds();

		bool shouldDestroy = selfRect.intersects(playerRect);
		return shouldDestroy;
	}

	bool Foe::IsOutOfBounds() {
		if (shape.getPosition().y > this->windowHeight + shape.getGlobalBounds().height) {
			return true;
		}
		return false;
	}

}