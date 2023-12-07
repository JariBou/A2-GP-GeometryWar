#include "Particle.h"


namespace SFX {

	Particle::Particle(sf::Shape& shape, float maxLifetime, sf::Vector2f direction) : Entities::DrawableEntity(shape), maxLifetime(maxLifetime), direction(direction) {

	}

	bool Particle::CheckLife() {
		return lifetime >= maxLifetime;
	}

	void Particle::Update(float deltaTime)
	{
		// TODO
	}

	void Particle::UpdateAlpha(float alpha)
	{
		sf::Color oldFillColor = shape.getFillColor();
		sf::Color newFillColor(oldFillColor.r, oldFillColor.g, oldFillColor.b, alpha);

		//sf::Color oldOutlineColor = shape.getOutlineColor();
		//sf::Color newOutlineColor(oldOutlineColor.r, oldOutlineColor.g, oldOutlineColor.b, alpha);

		shape.setFillColor(newFillColor);
		//shape.setOutlineColor(newOutlineColor);
	}

	float Particle::GetLifePercentage()
	{
		float percent = lifetime / maxLifetime;
		if (percent > 1) {
			return 1;
		}
		return lifetime / maxLifetime;
	}

}
