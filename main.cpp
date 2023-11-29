#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "src/entities/Entites.h"
#include "src/utils.h"


constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);
	// Début de la boucle de jeu
	sf::RectangleShape rectangle;
	sf::RectangleShape rectangleEnemy;
	Entities::Player player = Entities::Player(rectangle);
	Entities::LinearFoe enemy = Entities::LinearFoe(rectangleEnemy, 5);
	player.SetColor(sf::Color::Green);
	player.SetPosition(sf::Vector2f(640 - 64, 360 - 64));
	enemy.SetPosition(sf::Vector2f(640 - 32, 0));
	enemy.SetDirection(sf::Vector2f(0, 1));
	enemy.SetColor(sf::Color::Red);
	rectangle.setSize(sf::Vector2f(128, 128));
	rectangleEnemy.setSize(sf::Vector2f(64, 64));




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
		if (!enemy.isDead()) enemy.Update();

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		player.Draw(window);
		if (!enemy.isDead()) {
			enemy.Draw(window);
			std::cout << "PUTE" << std::endl;
		}

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
