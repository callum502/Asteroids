#include "AsteroidManager.h"
#include "Game.h"
#include "Asteroid.h"

AsteroidManager::AsteroidManager(Game& game_) : Entity(game_), spawnInterval(1.f) 
{
    asteroidTexture.loadFromFile("Assets/Asteroid.png");
    game.entities.push_back(this);
}

void AsteroidManager::SpawnAsteroid() 
{
    sf::Vector2f pos;
    sf::Vector2f vel;

    // pick a random side to spawn from
    if (rand() % 2 == 0)
    {
        if (rand() % 2 == 0)
        {
            //spawn along top
            pos.x = rand() % game.window.getSize().x;
            pos.y = 0;

            //y velocity is positive
            vel.y = rand() % 51 + 50;
            vel.x = rand() % 51 + 50;
            if (rand() % 2 == 0)
                vel.x *= -1;
        }
        else
        {
            //spawn along bottom
            pos.x = rand() % game.window.getSize().x;
            pos.y = game.window.getSize().y;


            //y velocity is negative
            vel.y = -1 * (rand() % 51 + 50);
            vel.x = rand() % 51 + 50;
            if (rand() % 2 == 0)
                vel.x *= -1;
        }
    }
    else
    {
        if (rand() % 2 == 0)
        {
            //spawn along left side
            pos.x = 0;
            pos.y = rand() % game.window.getSize().y;

            //x velocity is positive
            vel.x = rand() % 51 + 50;
            vel.y = rand() % 51 + 50;
            if (rand() % 2 == 0)
                vel.y *= -1;
		}
        else
        {
            //spawn along right side
            pos.x = game.window.getSize().x;
            pos.y = rand() % game.window.getSize().y;

            //x velocity is negative
            vel.x = -1 * (rand() % 51 + 50);
            vel.y = rand() % 51 + 50;
            if (rand() % 2 == 0)
                vel.y *= -1;
        }
	}
    float rotSpeed = rand() % 41 + 20; // 20 - 60
    sf::Vector2f scale;

    scale.x = (rand() % 76 + 175) / 100.f; // 1.75 - 2.5
    scale.y = (rand() % 76 + 175) / 100.f; // 1.75 - 2.5

    Asteroid* asteroid = new Asteroid(game, *this, asteroidTexture, pos, vel, rotSpeed, scale);

    game.entitiesToAdd.push_back(asteroid);
    asteroidCount += 4;
}

void AsteroidManager::Update(const float deltaTime) 
{
    // Check if it's time to spawn a new asteroid
    if (spawnTimer.getElapsedTime().asSeconds() > spawnInterval) 
    {
        if(asteroidCount<40)
            SpawnAsteroid();
        spawnTimer.restart();
        spawnInterval = 3 + (rand() % 3);  // 3 - 5 seconds
    }
}
