#include "States.h"
#include "../entities/Entites.h"
#include "../UpgradeBoxSpawner.h"
#include "../EnemySpawner.h"
#include "../WaveManager.h"
#include "../GameManager.h"
#include "../particles/ParticleSystem.h"

namespace States {
	GameState::GameState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score) : State(frameClock), score(score)
	{
		this->gameManager = new GameManager(window, score);
		this->gameManager->SetParticleSystem(new SFX::ParticleSystem());

		scoreText.setCharacterSize(40);
		scoreText.setPosition(5, 5);
		scoreText.setFont(MyFont);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setStyle(sf::Text::Bold);

		rectangle.setSize(sf::Vector2f(128, 128));
		player = new Entities::Player(rectangle, gameManager);
		player->SetColor(sf::Color::Transparent, sf::Color::Green);
		player->SetPosition(sf::Vector2f(640 - 64, 360 - 64));
		rectangle.setSize(sf::Vector2f(128, 128));
		player->SetPosition(sf::Vector2f((window.getSize().x / 2.), (window.getSize().y / 2.)));

		lifeText.setFont(MyFont);
		lifeText.setCharacterSize(50);
		lifeText.setFillColor(sf::Color::White);

		sf::FloatRect lifeBounds = lifeText.getLocalBounds();
		lifeText.setPosition((window.getSize().x - lifeBounds.width) / 2.0f + 670,
			(window.getSize().y - lifeBounds.height) / 2.0f - 520);

		this->upgradeBoxSpawner = new UpgradeBoxSpawner(upgradeBoxList, window.getSize().x, gameManager);
		this->enemySpawner = new EnemySpawner(&foeList, &window, gameManager);	

		anouncingWaveText.setCharacterSize(100);
		sf::FloatRect waveTextBounds = anouncingWaveText.getLocalBounds();
		anouncingWaveText.setPosition((window.getSize().x - waveTextBounds.width) / 2.0f - 100, (window.getSize().y - waveTextBounds.height) / 4.0f - 70);
		anouncingWaveText.setFont(MyFont);
		anouncingWaveText.setFillColor(sf::Color::White);
		anouncingWaveText.setStyle(sf::Text::Bold);

		this->waveManager = new WaveManager(enemySpawner, &anouncingWaveText, gameManager);
		waveManager->SetWave(0, 30);

		//GRID ACTIVATION
		grid = sf::VertexArray(sf::Lines);
		CreateNeonGrid(window.getSize().x, window.getSize().y);
	}

	void States::GameState::CreateNeonGrid(int windowWidth, int windowHeight)
	{
		const int gridSize = 150;
		const int numberOfLines = 15; // Nombre de lignes verticales et horizontales

		sf::Color color = sf::Color::Green;

		for (int i = 0; i < numberOfLines; ++i) {
			float thicknessFactor = static_cast<float>(i) / numberOfLines; // Facteur d'�paisseur bas� sur la distance du point de fuite

			// Lignes horizontales
			grid.append(sf::Vertex(sf::Vector2f(0, i * windowHeight / numberOfLines), color));
			grid.append(sf::Vertex(sf::Vector2f(windowWidth, i * windowHeight / numberOfLines), color));

			// Lignes verticales
			grid.append(sf::Vertex(sf::Vector2f(i * windowWidth / numberOfLines, 0), color));
			grid.append(sf::Vertex(sf::Vector2f(i * windowWidth / numberOfLines, windowHeight), color));
		}
	}

	void GameState::Restart(sf::RenderWindow& window) {
		foeList.clear();
		gameManager->Reset();

		player->lives = 3;
		player->SetPosition(sf::Vector2f((window.getSize().x / 2.), (window.getSize().y / 2.)));

		//On reset les niveaux des upgrades
		player->bulletDamageLevel = 1;
		player->bulletSpeedLevel = 1;
		player->movementSpeedLevel = 1;
		player->bulletNumberLevel = 1;

		//On reset les stats du joueur
		player->bulletCooldown = 0.5f;
		player->bulletDamage = 10;
		player->bulletSize = sf::Vector2f(5, 5);
		player->bulletClock = 0;
		player->nbBulletShot = 1;
		player->speed = 450.0;


		//On reset les vagues d'enemies
		waveManager->clock = 0;
		waveManager->waveCooldown = 3;
		waveManager->wave = 0;
		waveManager->anouncing = false;
		waveManager->SetWave(0, 30);

		//On reset le score
		score = 0;
		window.clear();
	}

	void GameState::Loop(sf::RenderWindow& window, int& sceneIndex)
	{
		if (!player->CheckLife()) {
			sceneIndex = 2;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			// On g�re l'�v�n�ment
			switch (event.type)
			{
			case sf::Event::Closed:
				// L'utilisateur a cliqu� sur la croix => on ferme la fen�tre
				window.close();
				break;

			default:
				break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;

		lifeText.setString("Life: " + std::to_string(player->lives));
		scoreText.setString("Score : " + Utils::toString(score));
		//std::cout<< "Score : " + Utils::toString(score);

		//upgradeBoxSpawner.TrySpawning(deltaTime);

		player->MovePlayer(deltaTime);

		player->Update(deltaTime); // This needs to change

		for (Entities::Bullet* bullet : *gameManager->GetBullets())
		{
			bullet->Update(deltaTime);
		}

		upgradeBoxSpawner->Update(deltaTime);

		for (Entities::Foe* en : *(enemySpawner->GetFoes())) {
			en->Update(deltaTime);
		}

		Utils::CheckBulletListLife(*gameManager->GetBullets());
		Utils::CheckFoeListLife(*(enemySpawner->GetFoes()));
		Utils::CheckUpgradeListLife(upgradeBoxSpawner->GetUpgradeBoxList());

		enemySpawner->Update(deltaTime);
		waveManager->Update(deltaTime);
 		this->gameManager->GetParticleSystem()->Update(deltaTime);

		// Affichage

		// Remise au noir de toute la fen�tre
		window.clear();

		// Tout le rendu va se d�rouler ici
		//window.draw(rectangle);

		window.draw(scoreText);
		if (waveManager->anouncing) window.draw(anouncingWaveText);
		player->Draw(window);

		window.draw(lifeText);
		window.draw(grid);

		for (Entities::Bullet* bullet : *gameManager->GetBullets())
		{
			bullet->Draw(window);
		}

		for (Entities::Foe* en : foeList) {
			en->Draw(window);
		}

		for (Entities::UpgradeBox* box : upgradeBoxSpawner->GetUpgradeBoxList()) {
			box->Draw(window);
		}

		this->gameManager->GetParticleSystem()->Draw(window);

		// On pr�sente la fen�tre sur l'�cran
		window.display();
	}

}

