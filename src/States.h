#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace Entities{
	class Foe;
	class UpgradeBox;
	class Player;
}

class UpgradeBoxSpawner;
class EnemySpawner;
class WaveManager;

namespace States {

	class State {
	public:
		State(sf::Clock& frameClock) : frameClock(frameClock){}

		virtual void Loop(sf::RenderWindow& window, int& sceneIndex) = 0;
		sf::Clock& frameClock;
	};


	class MenuState : public State{
	public:

		MenuState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock);

		void Loop(sf::RenderWindow& window, int& sceneIndex);
	private:
		std::vector<sf::Color> colorList = { sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Magenta };

		std::vector<sf::Text*> textList;
		float colorClock = 0;
		sf::Text gameTitle;
		sf::Text anyKeyText;
		sf::RectangleShape titleScreenRectangle;
	};

	class DeathState : public State{
	public:

		DeathState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score);

		void Loop(sf::RenderWindow& window, int& sceneIndex);

	private:
		std::vector<sf::Color> colorList = { sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Magenta };

		std::vector<sf::Text*> gameOvertextList;

		sf::Text gameOverTitle;
		sf::Text restartButton;
		sf::RectangleShape button;
		sf::Text creditText;
		sf::RectangleShape gameOverScreenRectangle;

		float colorClock = 0;
		int& score;
	};

	class GameState : public State{

	public:
		std::vector<Entities::Foe*> foeList;
		std::vector<Entities::UpgradeBox*> upgradeBoxList;
		UpgradeBoxSpawner* upgradeBoxSpawner;
		EnemySpawner* enemySpawner;
		WaveManager* waveManager;
		Entities::Player* player;
		sf::Text anouncingWaveText;

		GameState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score);

		void Loop(sf::RenderWindow& window, int& sceneIndex);

	private:
		sf::Text scoreText;
		sf::RectangleShape rectangle;
		int& score;


	};
}

