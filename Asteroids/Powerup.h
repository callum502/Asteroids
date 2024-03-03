#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

enum class PowerupType
{
	MultiShot,
	SpreadShot,
	Invincibility
};

class Powerup : public GameObject
{
public:
	Powerup(Game& game_, const sf::Texture& tex);
	void OnCollision(GameObject& other) override;
	void Update(float deltaTime) override;

private:
	PowerupType type;
	float duration = 10.f;
	float invisibleTimer = 0.f;
};

