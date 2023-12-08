#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

namespace SFX {

	class ParticleCompound;

	class ParticleSystem
	{
	public:
		ParticleSystem();
		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);
		void CheckLifetimes();

		void AddParticleCompound(ParticleCompound* compound);


#pragma region Prefabs

		void CreateExplosionAt(sf::Vector2f position, sf::Color color, float size = 3., int numberOfParticles=10);

#pragma endregion


	private:
		std::vector<ParticleCompound*> particleCompoundList;


	};


}
