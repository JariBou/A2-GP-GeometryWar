#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow& window)
{
	windowDimension = sf::Vector2f(window.getSize().x,window.getSize().y);
}

void GameManager::AddBullet(Entities::Bullet* bullet)
{
	bulletList.push_back(bullet);
}

std::vector<Entities::Bullet*>* GameManager::GetBullets()
{
	return &bulletList;
}
