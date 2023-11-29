#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "src/entities/Entites.h"


constexpr float cubeSpeed = 500.f;
using namespace Entities;

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);
	// Début de la boucle de jeu
	sf::RectangleShape rectangle;
	Entities::Player player = Entities::Player(rectangle);
	player.SetShapeType(Entities::ShapeType::OUTLINED);
	player.SetColor(sf::Color::Green);
	rectangle.setSize(sf::Vector2f(128, 128));




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
			moveVector.y = deltaTime * cubeSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			moveVector.y = -deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			moveVector.x =  -deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			moveVector.x = deltaTime * cubeSpeed;

		player.Move(moveVector);

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		player.Draw(window);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
