#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "src/entities/Entites.h"
#include "src/utils.h"


constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	

	// Début de la boucle de jeu
	sf::RectangleShape rectangle;
	Entities::Player player = Entities::Player(rectangle);
	player.SetColor(sf::Color::Transparent, sf::Color::Green);
	player.SetPosition(sf::Vector2f(640 - 64, 360 - 64));
	rectangle.setSize(sf::Vector2f(128, 128));


	
	std::vector<Entities::Foe*> foeList;

	for (int i = 0; i < 5; i++)
	{
		sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
		Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, i+1);
		enemy->SetPosition(sf::Vector2f(64 + 64*i, 0));
		enemy->SetDirection(sf::Vector2f(0, 1));
		enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
		rectangleEnemy->setSize(sf::Vector2f(64, 64));
		foeList.push_back(enemy);
	}


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

		// Logique
		sf::Vector2f moveVector;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			moveVector.y = -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			moveVector.y = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			moveVector.x =  -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			moveVector.x = 1;

		player.Move(Utils::NormalizeVector(moveVector) * cubeSpeed * deltaTime);
		for (Entities::Foe *en : foeList) {
			en->Update();
		};

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		player.Draw(window);

		for (Entities::Foe *en : foeList) {
			en->Draw(window);
		}
		

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
