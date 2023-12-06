#include "States.h"
#include "utils.h"


States::DeathState::DeathState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score) : State(frameClock), score(score){


	//GameTitle
	gameOverTitle.setString("Game Over");
	gameOverTitle.setCharacterSize(170);

	sf::FloatRect titleBounds = gameOverTitle.getLocalBounds();
	gameOverTitle.setPosition((window.getSize().x - titleBounds.width) / 2.0f - 450,
		(window.getSize().y - titleBounds.height) / 2.0f - 300);

	gameOvertextList.push_back(&gameOverTitle);

	//Restart Button
	restartButton.setString("Press to restart !");

	//button
	button.setSize(sf::Vector2f(550, 100));
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

	gameOverScreenRectangle.setSize(sf::Vector2f(window.getSize().x - 100, window.getSize().y - 100));
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
	creditText.setCharacterSize(40);

	for (int i = 0; i < 4; i++)
	{
		creditText.setString("Tome Bourdie");
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
}

void States::DeathState::Loop(sf::RenderWindow& window, int& sceneIndex) {
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
			sceneIndex = 1;
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
					sceneIndex = 1;
				}
			}
		}
	}

	float deltaTime = frameClock.restart().asSeconds();
	colorClock += deltaTime;

	if (colorClock >= 0.1) {
		gameOverTitle.setFillColor(colorList[rand() % colorList.size()]);
		gameOverScreenRectangle.setOutlineColor(colorList[rand() % colorList.size()]);
		colorClock = 0;
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