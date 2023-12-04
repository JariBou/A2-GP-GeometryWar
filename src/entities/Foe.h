#pragma once

#include "DrawableEntity.h"
#include "Player.h"

namespace Entities {

	class Foe : public DrawableEntity {

	public:

		float health = 20;
		float speed = 5;
		Player* player;

		Foe(sf::Shape& shape, float speed, Player* player) : DrawableEntity(shape), player(player) {
			this->speed = speed;
		}

		virtual void Update(float deltaTime) = 0;
		virtual bool isDead() = 0;
		virtual void OnKilledByPlayer() = 0;
		virtual void GetHit(float value) = 0;
	};

}
