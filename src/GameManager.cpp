#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::AddBullet(Entities::Bullet* bullet)
{
	bulletList.push_back(bullet);
}

std::vector<Entities::Bullet*>* GameManager::GetBullets()
{
	return &bulletList;
}
