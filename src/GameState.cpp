#include "States.h"
#include "entities/Entites.h"
#include "UpgradeBoxSpawner.h"
#include "EnemySpawner.h"
#include "WaveManager.h"

States::GameState::GameState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score) : State(frameClock), score(score) {
	scoreText.setCharacterSize(40);
	scoreText.setPosition(5, 5);
	scoreText.setFont(MyFont);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Bold);

	rectangle.setSize(sf::Vector2f(128, 128));
	player = new Entities::Player(rectangle);
	player->SetColor(sf::Color::Transparent, sf::Color::Green);
	player->SetPosition(sf::Vector2f(640 - 64, 360 - 64));
	rectangle.setSize(sf::Vector2f(128, 128));
	player->SetPosition(sf::Vector2f((window.getSize().x / 2.), (window.getSize().y / 2.)));
	player->SetWindow(window);

	lifeText.setFont(MyFont);
	lifeText.setCharacterSize(50);
	lifeText.setFillColor(sf::Color::White);

	sf::FloatRect lifeBounds = lifeText.getLocalBounds();
	lifeText.setPosition((window.getSize().x - lifeBounds.width) / 2.0f + 670,
		(window.getSize().y - lifeBounds.height) / 2.0f - 520);

	this->upgradeBoxSpawner = new UpgradeBoxSpawner(upgradeBoxList, window.getSize().x, *player);
	this->enemySpawner = new EnemySpawner(&foeList, &window, player);
	
	player->SetEnemySpawner(enemySpawner);
	player->SetBoxSpawner(upgradeBoxSpawner);

	anouncingWaveText.setCharacterSize(100);
	sf::FloatRect waveTextBounds = anouncingWaveText.getLocalBounds();
	anouncingWaveText.setPosition((window.getSize().x - waveTextBounds.width) / 2.0f - 100, (window.getSize().y - waveTextBounds.height) / 4.0f - 70);
	anouncingWaveText.setFont(MyFont);
	anouncingWaveText.setFillColor(sf::Color::White);
	anouncingWaveText.setStyle(sf::Text::Bold);

	this->waveManager = new WaveManager(enemySpawner, &anouncingWaveText);
	waveManager->SetWave(0, 30);

	//GRID ACTIVATION
	grid = sf::VertexArray(sf::Lines);
	CreateNeonGrid(window.getSize().x, window.getSize().y);
}

void States::GameState::CreateNeonGrid(int windowWidth, int windowHeight)
{
	const int gridSize = 150;
	const int numberOfLines = 15; // Nombre de lignes verticales et horizontales

	for (int i = 0; i < numberOfLines; ++i) {
		float thicknessFactor = static_cast<float>(i) / numberOfLines; // Facteur d'épaisseur basé sur la distance du point de fuite

		// Lignes horizontales
		grid.append(sf::Vertex(sf::Vector2f(0, i * windowHeight / numberOfLines), sf::Color::Green));
		grid.append(sf::Vertex(sf::Vector2f(windowWidth, i * windowHeight / numberOfLines), sf::Color::Green));

		// Lignes verticales
		grid.append(sf::Vertex(sf::Vector2f(i * windowWidth / numberOfLines, 0), sf::Color::Green));
		grid.append(sf::Vertex(sf::Vector2f(i * windowWidth / numberOfLines, windowHeight), sf::Color::Green));
	}
}

void States::GameState::Loop(sf::RenderWindow& window, int& sceneIndex) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		// On gère l'événément
		switch (event.type)
		{
		case sf::Event::Closed:
			// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
			window.close();
			break;

		default:
			break;
		}
		lifeText.setString("Life: " + std::to_string(player->lives));
	}

	float deltaTime = frameClock.restart().asSeconds();
	//std::cout << 1.f / deltaTime << " FPS" << std::endl;

	scoreText.setString("Score : " + Utils::toString(score));
	//std::cout<< "Score : " + Utils::toString(score);

	//upgradeBoxSpawner.TrySpawning(deltaTime);

	player->MovePlayer(deltaTime);

	player->Update(deltaTime); // This needs to change

	for (Entities::Bullet* bullet : player->GetBullets())
	{
		bullet->Update(deltaTime);
	}

	upgradeBoxSpawner->Update(deltaTime);

	for (Entities::Foe* en : foeList) {
		en->Update(deltaTime);
	}

	Utils::CheckBulletListLife(player->GetBullets());
	score += Utils::CheckFoeListLife(*(enemySpawner->GetFoes()));
	Utils::CheckUpgradeListLife(upgradeBoxSpawner->GetUpgradeBoxList());

	enemySpawner->Update(deltaTime);
	waveManager->Update(deltaTime);

	// Affichage

	// Remise au noir de toute la fenêtre
	window.clear();

	// Tout le rendu va se dérouler ici
	//window.draw(rectangle);

	window.draw(lifeText);
	window.draw(scoreText);
	window.draw(grid);

	if (waveManager->anouncing) window.draw(anouncingWaveText);
	player->Draw(window);

	for (Entities::Bullet* bullet : player->GetBullets())
	{
		bullet->Draw(window);
	}

	for (Entities::Foe* en : foeList) {
		en->Draw(window);
	}

	for (Entities::UpgradeBox* box : upgradeBoxSpawner->GetUpgradeBoxList()) {
		box->Draw(window);
	}

	// On présente la fenêtre sur l'écran
	window.display();
}