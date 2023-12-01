#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"


namespace Entities {
    class Player; // Assurez-vous que la classe Player est d�clar�e avant Bullet

    class Bullet : public DrawableEntity {
        public:
            int damage;
            float speed;
            Bullet(sf::Shape& shape, Player& player); // Utilisation d'une r�f�rence constante
            Bullet(sf::Shape& shape, Player& player, int damage, float speed, sf::Vector2f Direction); // Utilisation d'une r�f�rence constante
            virtual ~Bullet() = default;
            virtual bool MoveBullet(float deltaTime);
            virtual void Udapte(float deltaTime);
            virtual bool CheckLife();
            Player& player; // Utilisation d'une r�f�rence constante
    private :
			sf::Vector2f direction;
       
};
}