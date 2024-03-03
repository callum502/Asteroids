#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class AsteroidManager : public Entity
{
public:
    AsteroidManager(Game& game_);
    void Update(const float deltaTime) override;
    int asteroidCount = 0;

private:
    void SpawnAsteroid();

    sf::Texture asteroidTexture;
    sf::Clock spawnTimer;  // Timer for asteroid spawning
    float spawnInterval = 3;   // Interval between spawns (in seconds)
};
