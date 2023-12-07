#include "Player.h"
#include <iostream>
#include "../utils.h"
#include "../enum.h"
#include "Bullet.h"
#include "../GameManager.h"


namespace Entities 
{
	using namespace std;


	Player::Player(sf::Shape& shape, GameManager* pGameManager) : DrawableEntity(shape), gameManager(pGameManager) {
		gameManager->SetPlayer(this);
	}
	

	void Player::MovePlayer(float deltaTime)
	{
		sf::FloatRect boundingBox = shape.getLocalBounds();
		playerWidth = boundingBox.width + shape.getOutlineThickness()/2;
		playerHeight = boundingBox.height + shape.getOutlineThickness()/2;

		//cout << "player Witdh : " << playerHeight << ", player Height : " << playerHeight << endl;
		//cout << "x : " << shape.getPosition().x << ", y :" << shape.getPosition().y << endl;
		//cout << "Window Height : " << windowHeight << ", Window Width : " << windowWidth << endl << endl;
		sf::Vector2f moveVector;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			if (shape.getPosition().y - 1 > 0) {
				moveVector.y = -1;
			}
			/*moveVector.y = -1;*/
		}

			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if ((shape.getPosition().y + playerHeight) + 1 < windowHeight) {
				moveVector.y = 1;
			}
			/*moveVector.y = 1;*/
		}	

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if (shape.getPosition().x - 1 > 0)
			{
				moveVector.x = -1;
			}
			/*moveVector.x = -1;*/
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if ((shape.getPosition().x + playerWidth) + 1 < windowWidth)
			{
				moveVector.x = 1;
			}
			//moveVector.x = 1;
		}

		//std::cout << 1.f / deltaTime << " FPS" << std::endl;
		Move(Utils::NormalizeVector(moveVector) * speed * (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)? 0.8f : 1), deltaTime);
	}
    
    void Player::Draw(sf::RenderWindow& window){
		window.draw(this->shape);

		//Hitbox
		sf::RectangleShape rect;
		rect.setPosition(this->shape.getGlobalBounds().left, this->shape.getGlobalBounds().top);
		rect.setSize(sf::Vector2f(this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().height));
		rect.setOutlineThickness(2);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::White);
		window.draw(rect);
	}

	void Player::Update(float deltaTime)
	{
		bulletClock += deltaTime;
		if (bulletClock >= bulletCooldown) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				bulletClock = 0;
				// Largeur entre les balles
				float w = playerWidth / (nbBulletShot + 1);
				for (size_t i = 1; i <= nbBulletShot; i++) {
					sf::RectangleShape* rectangleBullet = new sf::RectangleShape(sf::Vector2f(bulletSize.x, bulletSize.y));
					float bulletSpeed = speed + 250.0 * bulletSpeedLevel / 8;
					float angle;
					// Vérifier le niveau de la mise à niveau des balles
					if (bulletNumberLevel <=2) {
						// Si le niveau est 1, tirer droit
						angle = 0;
					}
					else {
						// Calcul de l'angle de référence
						float bulletAngleRef = 0.5 / nbBulletShot;
						// Si la boucle est dans la première moitié des balles
						if (i <= (nbBulletShot / 2)) {
							// Si nécessaire, ajouter des angles de référence au vecteur
							if (bulletAngles.size() < nbBulletShot / 2) {
								bulletAngles.push_back(bulletAngleRef * i);
							}
							angle = -bulletAngles[bulletAngles.size() - i];
						}
						else {
							angle = bulletAngles[i - (nbBulletShot / 2) - 1];
						}
					}
					// Créer une nouvelle balle avec les paramètres calculés
					Bullet* bullet = new Bullet(*rectangleBullet, gameManager, bulletDamage, bulletSpeed, sf::Vector2f(angle, -1.0), windowWidth);
					bullet->SetColor(sf::Color::Yellow);
					bullet->SetPosition(sf::Vector2f(shape.getPosition().x + i * w - bulletSize.x / 2, shape.getPosition().y - rectangleBullet->getSize().y * 1.5));
					bullets.push_back(bullet);
				}
			}
		}
	}

	void Player::UpgradeLevel(UpgradeType upgrade)
	{
		switch (upgrade)
		{
		case UpgradeSpeed:
			if (movementSpeedLevel < 12) {
				movementSpeedLevel++;
				speed *= 1.1;
				cout << "Speed level : " << movementSpeedLevel << endl;
			}
			break;
		case UpgradeBulletDamage:
			if (bulletDamageLevel < 10) {
				bulletDamageLevel++;
				bulletDamage *= 1.1;
				bulletSize.x *= 1.1;
				bulletSize.y *= 1.1;
				cout << "Bullet damage level : " << bulletDamageLevel << endl;
			}
			break;
		case UpgradeBulletSpeed:
			if (bulletSpeedLevel < 8) {
				bulletSpeedLevel++;
				bulletCooldown -= 0.0325;
				cout << "Bullet speed level : " << bulletSpeedLevel << endl;
			}
			break;
		case UpgradeBulletNumber:
			if (bulletNumberLevel < 4) {
				bulletNumberLevel++;
				nbBulletShot*=2;
				cout << "Bullet number level : " << bulletNumberLevel << endl;
				bulletAngles.clear();
			}
			break;
		default:
			break;
		}
		
		/*if (upgradeLevel < 15) {
			upgradeLevel++;
			upgraded = true;
			cout << "Upgrade level : " << upgradeLevel << endl;
		}*/

	}

	void Player::GetHit(float damage) {
		std::cout << "Player hit" << std::endl;
		chanceCount--;
		if (chanceCount <= 0) {
			lives--;
			chanceCount = 3;
			std::cout << "Player lives : " << lives << std::endl;
		}
	}

	bool Player::CheckLife() {
		return (this->lives > 0);
	}

	EnemySpawner* Player::GetEnemySpawner() {
		return this->enemySpawner;
	}

	GameManager* Player::GetGameManager()
	{
		return gameManager;
	}

	UpgradeBoxSpawner* Player::GetBoxSpawner()
	{
		return this->boxSpawner;
	}

	std::vector<Bullet*>& Player::GetBullets() 
	{
		return bullets;
	}

	std::vector<DrawableEntity*>& Player::GetBulletEntities()
	{
		std::vector<DrawableEntity*> vec;
		for (Bullet* bullet : bullets) {
			vec.push_back(bullet);
		}
		return vec;
	}
}
	




	