#pragma once

#include "DrawableEntity.h"

namespace Entities {

	class Foe : public DrawableEntity {

	public:

		float health = 20;
		float speed = 5;

		Foe(sf::Shape& shape, float speed);

		virtual void Update() = 0;
		virtual bool isDead() = 0;

		virtual void GetHit(float value) = 0;
	};

}
