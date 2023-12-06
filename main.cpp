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

	//Score:

	sf::Font MyFont;
	if (!MyFont.loadFromFile("../font/Roboto-Black.ttf"))
	{
		// Erreur...
	}

	sf::Text scoreText;
	int score = 0;
	scoreText.setCharacterSize(40);
	scoreText.setPosition(5, 5);
	scoreText.setFont(MyFont);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Bold);


	sf::RectangleShape rectangle(sf::Vector2f(128,128));
	Entities::Player player = Entities::Player(rectangle);
	player.SetColor(sf::Color::Transparent, sf::Color::Green);
	player.SetPosition(sf::Vector2f(640 - 64, 360 - 64));
	rectangle.setSize(sf::Vector2f(128, 128));
	player.SetPosition(sf::Vector2f((window.getSize().x / 2.), (window.getSize().y / 2.)));
	player.SetWindow(window);

	
	std::vector<Entities::Foe*> foeList;

	std::vector<sf::Vector2f> spawnPoints;
	std::vector<Entities::UpgradeBox*> upgradeBoxList;
	UpgradeBoxSpawner upgradeBoxSpawner = UpgradeBoxSpawner(upgradeBoxList, window.getSize().x, player);
	EnemySpawner enemySpawner = EnemySpawner(&foeList, &window, &player);
	player.SetEnemySpawner(&enemySpawner);
	player.SetBoxSpawner(&upgradeBoxSpawner);

	spawnPoints.push_back(sf::Vector2f(1800, 0));
	spawnPoints.push_back(sf::Vector2f(1500, 0));
	spawnPoints.push_back(sf::Vector2f(1000, 0));
	spawnPoints.push_back(sf::Vector2f(700, 0));
	spawnPoints.push_back(sf::Vector2f(300, 0));

	enemySpawner.setSpawnPoints(spawnPoints);
	enemySpawner.StartClock();

	sf::Clock frameClock;
	float UpgradeSpawningCooldown = 2;
	int _scene = 0;
	

	#pragma region TitleScreen

	std::vector<sf::Color> colorList = {sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Magenta};

	std::vector<sf::Text*> textList;

	sf::Text gameTitle;
	gameTitle.setString("Title of the Game");
	gameTitle.setCharacterSize(170);
	gameTitle.setPosition(270, window.getSize().y / 8);
	textList.push_back(&gameTitle);

	sf::Text anyKeyText;
	anyKeyText.setString("Press any key to continue !");
	anyKeyText.setPosition(600, window.getSize().y / 2);
	anyKeyText.setCharacterSize(60);
	textList.push_back(&anyKeyText);

	sf::RectangleShape titleScreenRectangle(sf::Vector2f(window.getSize().x - 100, window.getSize().y - 100));
	titleScreenRectangle.setOutlineColor(sf::Color::White);
	titleScreenRectangle.setFillColor(sf::Color::Transparent);
	titleScreenRectangle.setOutlineThickness(10);
	titleScreenRectangle.setPosition(sf::Vector2f(30, 30));

	for (sf::Text* text : textList)
	{
		text->setFont(MyFont);
		text->setFillColor(sf::Color::White);
		text->setStyle(sf::Text::Bold);
	}

	float colorClock = 0;

	while (window.isOpen() && _scene==0)
	{
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

			case sf::Event::KeyPressed:
				_scene = 1;
				break;
			default:
				break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();
		colorClock += deltaTime;

		if (colorClock >= 0.3) {
			gameTitle.setFillColor(colorList[rand() % colorList.size()]);
			titleScreenRectangle.setOutlineColor(colorList[rand() % colorList.size()]);
			colorClock = 0;
		}


		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici

		for (sf::Text* text : textList)
		{
			window.draw(*text);
		}
		window.draw(titleScreenRectangle);

		// On présente la fenêtre sur l'écran
		window.display();
		
	}

	#pragma endregion TitleScreen

	#pragma region DeadScreen

		std::vector<sf::Color> colorsList = { sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Magenta };

		std::vector<sf::Text*> gameOvertextList;

		//GameTitle
		sf::Text gameOverTitle;
		gameOverTitle.setString("Game Over");
		gameOverTitle.setCharacterSize(170);

		sf::FloatRect titleBounds = gameOverTitle.getLocalBounds();
		gameOverTitle.setPosition((window.getSize().x - titleBounds.width) / 2.0f - 450,
			(window.getSize().y - titleBounds.height) / 2.0f - 300);

		gameOvertextList.push_back(&gameOverTitle);

		//Restart Button
		sf::Text restartButton;
		restartButton.setString("Press to restart !");

		//button
		sf::RectangleShape button(sf::Vector2f(550, 100)); // Crée un bouton rectangulaire
		button.setFillColor(sf::Color::Green);
		button.setPosition(300, 250);
		button.setFillColor(sf::Color::Transparent);
		button.setOutlineThickness(5);


		sf::FloatRect buttonBounds = button.getLocalBounds();
		button.setPosition((window.getSize().x - buttonBounds.width) / 2.0f + 25,
			(window.getSize().y - buttonBounds.height) / 2.0f + 100);

		sf::FloatRect restartButtonBounds = restartButton.getLocalBounds();
		restartButton.setPosition((window.getSize().x - restartButtonBounds.width) / 2.0f - 200,
			(window.getSize().y - restartButtonBounds.height) / 2.0f + 50);

		restartButton.setCharacterSize(60);
		gameOvertextList.push_back(&restartButton);

		sf::RectangleShape gameOverScreenRectangle(sf::Vector2f(window.getSize().x - 100, window.getSize().y - 100));
		gameOverScreenRectangle.setOutlineColor(sf::Color::White);
		gameOverScreenRectangle.setFillColor(sf::Color::Transparent);
		gameOverScreenRectangle.setOutlineThickness(10);
		gameOverScreenRectangle.setPosition(sf::Vector2f(30, 30));

		//Score
		sf::Text endScoreText;
		endScoreText.setString("Your score : " + Utils::toString(score));

		sf::FloatRect scoreTextBounds = endScoreText.getLocalBounds();
		endScoreText.setPosition((window.getSize().x - scoreTextBounds.width) / 2.0f - 100,
			(window.getSize().y - scoreTextBounds.height) / 2.0f - 70);

		endScoreText.setCharacterSize(40);
		gameOvertextList.push_back(&endScoreText);

		endScoreText.setFont(MyFont);
		endScoreText.setFillColor(sf::Color::White);
		endScoreText.setStyle(sf::Text::Bold);

		//Credit
		sf::Text creditText;
		creditText.setCharacterSize(40);

		for (int i = 0; i < 4; i++)
		{
			creditText.setString("Tome bourdie");
			if (i == 1) creditText.setString("Volodia Bussereau");
			if (i == 2) creditText.setString("Shahine Benthanane");
			if (i == 3) creditText.setString("Pierre Lamare");

			sf::FloatRect creditBounds = creditText.getLocalBounds();
			creditText.setPosition((window.getSize().x - creditBounds.width) / 2.0f - 150,
				(window.getSize().y - creditBounds.height) / 2.0f + 200 + i * 60); // Modifiez cette valeur pour changer l'écart entre les titres

			gameOvertextList.push_back(new sf::Text(creditText));
		}

		for (sf::Text* text : gameOvertextList)
		{
			text->setFont(MyFont);
			text->setFillColor(sf::Color::White);
			text->setStyle(sf::Text::Bold);
		}

		float colorsClock = 0;

		while (window.isOpen() && _scene == 2)
		{
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

				case sf::Event::KeyPressed:
					_scene = 1;
					break;
				default:
					break;
				}

				if (event.type == sf::Event::MouseButtonReleased) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						if (button.getGlobalBounds().contains(mousePosition)) {
							// Action à effectuer lorsque le bouton est cliqué
							button.setFillColor(sf::Color::Red);
							_scene = 1;
						}
					}
				}
			}

			float deltaTime = frameClock.restart().asSeconds();
			colorsClock += deltaTime;

			if (colorsClock >= 0.1) {
				gameOverTitle.setFillColor(colorsList[rand() % colorsList.size()]);
				gameOverScreenRectangle.setOutlineColor(colorsList[rand() % colorsList.size()]);
				colorsClock = 0;
			}


			// Remise au noir de toute la fenêtre
			window.clear();

			// Tout le rendu va se dérouler ici

			for (sf::Text* text : gameOvertextList)
			{
				window.draw(*text);
			}
			window.draw(gameOverScreenRectangle);
			window.draw(button);

			// On présente la fenêtre sur l'écran
			window.display();

		}

	#pragma endregion DeadScreen
	//endregion
	

	while (window.isOpen() && _scene==1)
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

		scoreText.setString("Score : " + Utils::toString(score));
		//std::cout<< "Score : " + Utils::toString(score);

		//upgradeBoxSpawner.TrySpawning(deltaTime);

		player.MovePlayer(deltaTime);

		player.Update(deltaTime); // This needs to change

		for (Entities::Bullet* bullet : player.GetBullets())
		{
			bullet->Update(deltaTime);
		}

		upgradeBoxSpawner.Update(deltaTime);

		for (Entities::Foe *en : foeList) {
			en->Update(deltaTime);
		}		

		Utils::CheckBulletListLife(player.GetBullets());
		score += Utils::CheckFoeListLife(*(enemySpawner.GetFoes()));
		Utils::CheckUpgradeListLife(upgradeBoxSpawner.GetUpgradeBoxList());
		
		enemySpawner.Update(deltaTime);

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		
		window.draw(scoreText);
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