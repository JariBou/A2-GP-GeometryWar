#include <SFML/Window.hpp>
#include <iostream>
#include "src/States.h"


int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	srand(time(NULL));

	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Hand)) {
		window.setMouseCursor(cursor);
	}

	sf::Font MyFont;
	if (!MyFont.loadFromFile("../font/Roboto-Black.ttf"))
	{
		std::cout << "Erreur" << std::endl;
	}

	sf::Clock frameClock;
	int _scene = 0;
	int score = 0;

	States::MenuState menuState(window, MyFont, frameClock);
	States::GameState gameState(window, MyFont, frameClock, score);
	States::DeathState deathState(window, MyFont, frameClock, score);

	while (window.isOpen())
	{
		if (_scene == 0) {
			window.setMouseCursorVisible(true);
			menuState.Loop(window, _scene);
		}
		else if (_scene == 1) {
			window.setMouseCursorVisible(false);
			gameState.Loop(window, _scene);
		}
		else if (_scene == 2) {
			window.setMouseCursorVisible(true);
			deathState.Loop(window, _scene);
		}
	}
	
}