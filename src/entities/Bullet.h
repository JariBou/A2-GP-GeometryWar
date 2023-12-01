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
        Bullet(sf::Shape& shape, Player& Joueur); // Utilisation d'une r�f�rence constante
        virtual ~Bullet() = default;
        virtual void MoveBullet(float deltaTime);
        virtual void Udapte(float deltaTime);
        Player& player; // Utilisation d'une r�f�rence constante
    };
}