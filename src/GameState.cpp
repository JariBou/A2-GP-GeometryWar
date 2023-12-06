#include "States.h"
#include "entities/Entites.h"
#include "UpgradeBoxSpawner.h"
#include "EnemySpawner.h"

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



	std::vector<sf::Vector2f> spawnPoints;
	this->upgradeBoxSpawner = new UpgradeBoxSpawner(upgradeBoxList, window.getSize().x, *player);
	this->enemySpawner = new EnemySpawner(&foeList, &window, player);
	player->SetEnemySpawner(enemySpawner);
	player->SetBoxSpawner(upgradeBoxSpawner);

	spawnPoints.push_back(sf::Vector2f(1800, 0));
	spawnPoints.push_back(sf::Vector2f(1500, 0));
	spawnPoints.push_back(sf::Vector2f(1000, 0));
	spawnPoints.push_back(sf::Vector2f(700, 0));
	spawnPoints.push_back(sf::Vector2f(300, 0));

	enemySpawner->setSpawnPoints(spawnPoints);
	enemySpawner->StartClock();
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

	// Affichage

	// Remise au noir de toute la fenêtre
	window.clear();

	// Tout le rendu va se dérouler ici
	//window.draw(rectangle);

	window.draw(scoreText);
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