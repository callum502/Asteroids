#include "PowerupManager.h"
#include "Game.h"
#include "Powerup.h"

PowerupManager::PowerupManager(Game& game_) : Entity(game_)
{
    powerupTexture.loadFromFile("Assets/Powerup.png");
    game.entities.push_back(this);
}

void PowerupManager::Update(float deltaTime)
{
    // Check if it's time to spawn a new asteroid
    if (spawnTimer.getElapsedTime().asSeconds() > spawnInterval) 
    {
        SpawnPowerup();
        spawnTimer.restart();
        spawnInterval = 15 + (rand() % 6);  // 15 - 20 seconds
    }
}

void PowerupManager::SpawnPowerup()
{
	Powerup* powerup = new Powerup(game, powerupTexture);
	game.entitiesToAdd.push_back(powerup);

}
