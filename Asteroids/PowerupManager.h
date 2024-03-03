#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class PowerupManager : public Entity
{
public:
	PowerupManager(Game& game_);
	void Update(float deltaTime) override;

private:
	void SpawnPowerup();
	
	sf::Clock spawnTimer;
	float spawnInterval = 3;
	sf::Texture powerupTexture;
};

