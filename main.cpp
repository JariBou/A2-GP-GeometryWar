#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "src/entities/Entites.h"
#include "src/utils.h"
#include "src/EnemySpawner.h"
#include "src/entities/Player.h"
#include "src/entities/Bullet.h"




int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	srand(time(NULL));

	// Début de la boucle de jeu
	sf::RectangleShape rectangle;
	Entities::Player player = Entities::Player(rectangle);
	player.SetColor(sf::Color::Transparent, sf::Color::Green);
	player.SetPosition(sf::Vector2f(640 - 64, 360 - 64));
	rectangle.setSize(sf::Vector2f(128, 128));
	player.SetPosition(sf::Vector2f((window.getSize().x / 2.), (window.getSize().y / 2.)));
	player.SetWindow(window);
	float cubeSpeed = 500.f;


	
	std::vector<Entities::Foe*> foeList;

	std::vector<sf::Vector2f> spawnPoints;
	EnemySpawner spawner = EnemySpawner(&foeList, &window);

	spawnPoints.push_back(sf::Vector2f(128, 0));
	spawnPoints.push_back(sf::Vector2f(156, 0));
	spawnPoints.push_back(sf::Vector2f(32, 0));

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
		std::cout << 1.f / deltaTime << " FPS" << std::endl;


		player.MovePlayer(deltaTime);

		player.ShootPlayer(); // This needs to change

		for (Entities::Foe *en : foeList) {
			en->Update(deltaTime);
		}

		for (Entities::Bullet* bullet : player.GetBullets())
		{
			bullet->MoveBullet(deltaTime);
		}

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
		

		// On présente la fenêtre sur l'écran
		window.display();
	}
}