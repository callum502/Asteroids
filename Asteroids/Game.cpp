#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "AsteroidManager.h"
#include "Powerup.h"
#include "PowerupManager.h"
#include "UI.h"

Game::Game()
{
    Initialize();
}

void Game::Run() 
{
    while (window.isOpen()) 
    {
        HandleEvents();
        Update();
        Render();
    }
}

// Restart game, reset all variables
void Game::Restart()
{
    gameOver = false;
    score = 0;

    for (auto& entity : entities)
    {
        delete entity;
    }
    entities.clear();

    for (auto& entity : entitiesToAdd)
    {
		delete entity;
	}
    entitiesToAdd.clear();

    player = new Player(*this);
    asteroidManager = new AsteroidManager(*this);
    powerupManager = new PowerupManager(*this);

    music.play();
}

// Initialize window and game components
void Game::Initialize() 
{
    window.create(sf::VideoMode(800, 800), "LHG Code Exercise");

    ui = new UI(*this);
    asteroidManager = new AsteroidManager(*this);
    powerupManager = new PowerupManager(*this);
    player = new Player(*this);

    music.openFromFile("Assets/music.wav");
    music.setLoop(true);
    music.play();
}

void Game::HandleEvents() 
{
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::Update() 
{
    const float deltaTime = gameClock.restart().asSeconds();

    // Loop through entities and delete if dead
    for (auto it = entities.begin(); it < entities.end();)
    {
        if ((*it)->dead)
        {
			delete *it;
			it = entities.erase(it);
		}
        else
        {
			++it;
        }

	}
    
    //loop through entities and update
    for (auto& entity : entities)
    {
		entity->Update(deltaTime);
	}

    // Add new entities
    entities.insert(entities.end(), entitiesToAdd.begin(), entitiesToAdd.end());
    entitiesToAdd.clear();

    // Check for collisions
    for (auto it = entities.begin(); it < entities.end(); ++it)
    {
        for (auto it2 = it + 1; it2 < entities.end(); ++it2)
        {
            GameObject* a = dynamic_cast<GameObject*>(*it);
            GameObject* b = dynamic_cast<GameObject*>(*it2);

            if (a != nullptr && b != nullptr)
            {
                if (a->TestCollision(*b))
                {
                    a->OnCollision(*b);
                    b->OnCollision(*a);
                }
            }
        }
    }
}

void Game::Render() 
{
    // Draw entities and UI
    window.clear();

    for (auto& entity : entities)
    {
        GameObject* gameObject = dynamic_cast<GameObject*>(entity);
        if(gameObject != nullptr)
            gameObject->Draw();
	}
    ui->Render(); // Draw UI last

    window.display();
}
