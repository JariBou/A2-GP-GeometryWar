#include "ParticleCompound.h"
#include "Particle.h"


namespace SFX {
	ParticleCompound::ParticleCompound()
	{
	}
	void ParticleCompound::Update(float deltaTime) {

		this->CheckLifetimes();

		for (Particle* pParticle : this->particlesList) {
			pParticle->Update(deltaTime);
		}
	}

	

	void ParticleCompound::Draw(sf::RenderWindow& window) {
		for (Particle* pParticle : this->particlesList) {
			pParticle->UpdateAlpha(1 - pParticle->GetLifePercentage());
			pParticle->Draw(window);
		}
	}

	void ParticleCompound::CheckLifetimes()
	{
		auto it = this->particlesList.begin();
		while (it != this->particlesList.end())
		{
			if ((*it)->CheckLife()) {
				it++;
			}
			else {
				it = this->particlesList.erase(it);
			}
		}
	}

	bool ParticleCompound::IsActive()
	{
		return this->particlesList.size() > 0;
	}

}