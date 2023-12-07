#include "ParticleSystem.h"
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

	ParticleCompound ParticleSystem::CreateExplosionAt(sf::Vector2f position, sf::Color color, float size = 4.)
	{
		std::vector<Particle*> particles;

		sf::RectangleShape particleShape(sf::Vector2f(size, size));
		Particle* pNewParticle = new Particle(particleShape, 1., sf::Vector2f(1, 0));

		particles.push_back(pNewParticle);



		return ParticleCompound();
	}

}
