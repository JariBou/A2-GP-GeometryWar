#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include "src/entities/Entites.h"
#include "src/utils.h"
#include "src/EnemySpawner.h"
#include "src/entities/Player.h"
#include "src/entities/Bullet.h"
#include "src/entities/UpgradeBox.h"
#include "src/UpgradeBoxSpawner.h"




int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	srand(time(NULL));

	// Début de la boucle de jeu
	sf::RectangleShape rectangle(sf::Vector2f(128,128));
	Entities::Player player = Entities::Player(rectangle);
	player.SetColor(sf::Color::Transparent, sf::Color::Green);
	player.SetPosition(sf::Vector2f(640 - 64, 360 - 64));
	rectangle.setSize(sf::Vector2f(128, 128));
	player.SetPosition(sf::Vector2f((window.getSize().x / 2.), (window.getSize().y / 2.)));
	player.SetWindow(window);
	float cubeSpeed = 500.f;


	
	std::vector<Entities::Foe*> foeList;

	std::vector<sf::Vector2f> spawnPoints;
	EnemySpawner spawner = EnemySpawner(&foeList, &window, &player);
	std::vector<Entities::UpgradeBox*> upgradeBoxList;
	UpgradeBoxSpawner upgradeBoxSpawner = UpgradeBoxSpawner(upgradeBoxList, window.getSize().x, player);
	player.enemySpawner = &spawner;

	spawnPoints.push_back(sf::Vector2f(1800, 0));
	spawnPoints.push_back(sf::Vector2f(1500, 0));
	spawnPoints.push_back(sf::Vector2f(1000, 0));
	spawnPoints.push_back(sf::Vector2f(700, 0));
	spawnPoints.push_back(sf::Vector2f(300, 0));

	spawner.setSpawnPoints(spawnPoints);
	spawner.StartClock();

	/*for (int i = 0; i < 5; i++)
	{
		sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
		Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, i+1);
		enemy->SetPosition(sf::Vector2f(64 + 64*i, 0));
		enemy->SetDirection(sf::Vector2f(0, 1));
		enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
		enemy->SetWindow(window);
		rectangleEnemy->setSize(sf::Vector2f(64, 64));
		foeList.push_back(enemy);
	}*/

	/*for (int i = 0; i < 5; i++)
	{
		spawner.SpawnEnemy(i);
	}*/


	sf::Clock frameClock;
	float UpgradeSpawningCooldown = 2;
	

	while (window.isOpen())
	{
		// Gérer les événéments survenus depuis le dernier tour de boucle
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

		upgradeBoxSpawner.TrySpawning(deltaTime);

		player.MovePlayer(deltaTime);

		player.Update(deltaTime); // This needs to change

		for (Entities::Bullet* bullet : player.GetBullets())
		{
			bullet->Update(deltaTime);
		}

		upgradeBoxSpawner.Update(deltaTime);


		/*auto bulletVectorIterator = player.GetBullets().begin();
		while (bulletVectorIterator != player.GetBullets().end()) {
			if ((*bulletVectorIterator)->CheckLife()) {
				bulletVectorIterator++;
			}
			else {
				bulletVectorIterator = player.GetBullets().erase(bulletVectorIterator);
				std::cout << "Bullet deleted" << std::endl;
			}
		}*/


		for (Entities::Foe *en : foeList) {
			en->Update(deltaTime);
		}		

		Utils::CheckBulletListLife(player.GetBullets());
		Utils::CheckFoeListLife(*(spawner.GetFoes()));

		Utils::CheckUpgradeListLife(upgradeBoxSpawner.GetUpgradeBoxList());
		
		/*Utils::CheckEntityListLife(player.GetBulletEntities());
		Utils::CheckEntityListLife(spawner.GetFoeEntities());
		Utils::CheckEntityListLife(upgradeBoxSpawner.GetUpgradeBoxEntities());
		*/


		// Utils::CheckEntityListLife(player.GetBullets());
		
		
		
		spawner.Update(deltaTime);

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		
		player.Draw(window);

		for (Entities::Bullet* bullet : player.GetBullets())
		{
			bullet->Draw(window);
		}

		for (Entities::Foe *en : foeList) {
			en->Draw(window);
		}

		for (Entities::UpgradeBox* box : upgradeBoxSpawner.GetUpgradeBoxList()) {
			box->Draw(window);
		}
		
		// On présente la fenêtre sur l'écran
		window.display();
	}
}