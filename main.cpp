#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "src/entities/Entites.h"
#include "src/utils.h"
#include "src/entities/Player.h"
#include "src/entities/Bullet.h"




int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	// Début de la boucle de jeu
	sf::RectangleShape rectangle;
	Entities::Player player = Entities::Player(rectangle);
	player.SetColor(sf::Color::Green);
	rectangle.setSize(sf::Vector2f(128, 128));
	player.SetPosition(sf::Vector2f((window.getSize().x / 2), (window.getSize().y / 2)));
	player.GetWindowwSize(window);




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
		

		player.MovePlayer();
		player.ShootPlayer();

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		player.Draw(window);
		for (Entities::Bullet& bullet : player.GetBullets())
		{
			bullet.Udapte(frameClock.restart().asSeconds());
			bullet.Draw(window);
		}

		// On présente la fenêtre sur l'écran
		window.display();
	}
}