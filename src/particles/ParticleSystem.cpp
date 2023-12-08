#include "ParticleSystem.h"
#include <cmath>
#include "Particle.h"
#include "ParticleCompound.h"

namespace SFX {

	ParticleSystem::ParticleSystem()
	{

	}

	void ParticleSystem::Update(float deltaTime)
	{
		for (ParticleCompound* pParticleCompound : this->particleCompoundList) {
			pParticleCompound->Update(deltaTime);
		}
	}

	void ParticleSystem::Draw(sf::RenderWindow& window)
	{
		for (ParticleCompound* pParticleCompound : this->particleCompoundList) {
			pParticleCompound->Draw(window);
		}
	}

	void ParticleSystem::CheckLifetimes()
	{
		auto it = this->particleCompoundList.begin();
		while (it != this->particleCompoundList.end())
		{
			if ((*it)->IsActive()) {
				it++;
			}
			else {
				it = this->particleCompoundList.erase(it);
			}
		}
	}

	void ParticleSystem::AddParticleCompound(ParticleCompound* compound)
	{
		this->particleCompoundList.push_back(compound);
	}

	void ParticleSystem::CreateExplosionAt(sf::Vector2f position, sf::Color color, float size, int numberOfParticles)
	{
		ParticleCompound* explosionCompound = new ParticleCompound();

		int directionAngle = 360 / numberOfParticles;

		float testingAngle = 0;

		for (int i = 0; i < numberOfParticles; i++)
		{
			float angle = testingAngle + (rand() % directionAngle) - directionAngle / 2.;

			float x = cos(angle);
			float y = sin(angle);

			sf::RectangleShape* particleShape = new sf::RectangleShape(sf::Vector2f(size, size));
			particleShape->setPosition(position);
			particleShape->setFillColor(color);

			float speed = ((rand() % 300) / 100.) + 35;
			Particle* pNewParticle = new Particle(*particleShape, 1., sf::Vector2f(x, y), speed);

			explosionCompound->AddParticle(pNewParticle);

			testingAngle += directionAngle;
		}

		AddParticleCompound(explosionCompound);
	}

}
