#include "Asteroid.h"
#include "Bullet.h"
#include "AsteroidManager.h"
#include "Game.h"

Asteroid::Asteroid(Game& game, AsteroidManager& asteroidManager_, const sf::Texture& texture, sf::Vector2f position, sf::Vector2f velocity_, float rotationSpeed_, sf::Vector2f scale) : GameObject(game), asteroidManager(asteroidManager_)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    velocity = velocity_;
    rotationSpeed = rotationSpeed_;
    sprite.setScale(scale);

    sprite.setColor(sf::Color(134, 106, 82)); // Brown
}

void Asteroid::Update(const float deltaTime) 
{
    sf::RenderWindow& window = game.window;

    sprite.move(velocity * deltaTime);
    sprite.rotate(rotationSpeed * deltaTime);
    
    // Wrap around the screen
    if (sprite.getPosition().x > window.getSize().x)
        sprite.setPosition(0, sprite.getPosition().y);
    else if (sprite.getPosition().x < 0)
        sprite.setPosition(window.getSize().x, sprite.getPosition().y);
    if (sprite.getPosition().y > window.getSize().y)
        sprite.setPosition(sprite.getPosition().x, 0);
    else if (sprite.getPosition().y < 0)
        sprite.setPosition(sprite.getPosition().x, window.getSize().y);
}

// Create 2 new asteroids of smaller size, faster velocity, opposite directions
void Asteroid::Split()
{
    sf::Vector2f vel;
    vel.x = rand() % 101 + 50;
    vel.y = rand() % 101 + 50;


    if (rand() % 2 == 0)
		vel.x = -vel.x;
    if (rand() % 2 == 0)
        vel.y = -vel.y;

    if (size == AsteroidSize::Medium)
        vel += sf::Vector2f(50.f, 50.f);

    sf::Vector2f scale = sprite.getScale() - sf::Vector2f(0.5f, 0.5f);

    Asteroid* a1 = new Asteroid(game, asteroidManager, *sprite.getTexture(), sprite.getPosition(), vel, 20.f, scale);
    Asteroid* a2 = new Asteroid(game, asteroidManager, *sprite.getTexture(), sprite.getPosition(), -vel, 20.f, scale);
        
    a1->size = size == AsteroidSize::Large ? AsteroidSize::Medium : AsteroidSize::Small;
    a2->size = size == AsteroidSize::Large ? AsteroidSize::Medium : AsteroidSize::Small;

    game.entitiesToAdd.push_back(a1);
    game.entitiesToAdd.push_back(a2);
}

void Asteroid::OnCollision(GameObject& other)
{
    if (dynamic_cast<Bullet*>(&other))
    {
		dead = true;
        other.dead = true;
        if(!game.gameOver) // Don't add score from bullets remaining on screen after game over
		    game.score += 10;

        if(size != AsteroidSize::Small)
		    Split();
        else
            asteroidManager.asteroidCount--;
	}
}
