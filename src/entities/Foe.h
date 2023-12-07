#pragma once

#include "DrawableEntity.h"
#include "Player.h"

namespace Entities {

	class Foe : public DrawableEntity {

	public:

		float health = 20;
		float speed = 5;
		Player* player;

		Foe(sf::Shape& shape, float speed, Player* player);

		//virtual void Update(float deltaTime);
		//virtual bool isDead();
		virtual void OnKilledByPlayer();
		virtual void GetHit(float value);
		virtual bool IsCollidingWithPlayer();
	};

}
