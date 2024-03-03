#pragma once
#include "GameObject.h"
#include "Asteroid.h"

class Bullet : public GameObject
{
public:
	Bullet(Game& game, const sf::Texture& texture, sf::Vector2f position, sf::Vector2f velocity_);
	void Update(const float deltaTime) override;

private:
	sf::Vector2f velocity;
};

