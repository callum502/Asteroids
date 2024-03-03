#include "Player.h"
#include "Game.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Powerup.h"

Player::Player(Game& game) : GameObject(game)
{
    Initialize();
}

void Player::Initialize() 
{
    texture.loadFromFile("Assets/Ship.png");
    bulletTexture.loadFromFile("Assets/Asteroid.png");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(game.window.getSize().x / 2, game.window.getSize().y / 2);
    game.entities.push_back(this);
}

void Player::Update(const float deltaTime)
{
    //move forward
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
    {
        float radians = (sprite.getRotation()-90) * (3.14159265358979323846 / 180.0f);
        sf::Vector2f direction = sf::Vector2f(std::cos(radians), std::sin(radians));
        sprite.move(movementSpeed * direction * deltaTime); 
    }

    // Rotate
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
    {
        sprite.rotate(-rotationSpeed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
    {
        sprite.rotate(rotationSpeed * deltaTime);
    }

    sf::RenderWindow& window = game.window;
    // Wrap around the screen
    if (sprite.getPosition().x > window.getSize().x)
        sprite.setPosition(0, sprite.getPosition().y);
    else if (sprite.getPosition().x < 0)
        sprite.setPosition(window.getSize().x, sprite.getPosition().y);
    if (sprite.getPosition().y > window.getSize().y)
		sprite.setPosition(sprite.getPosition().x, 0);
    else if (sprite.getPosition().y < 0) 
		sprite.setPosition(sprite.getPosition().x, window.getSize().y);

    // Fire bullet
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer < 0.f)
    {
        float radians = (sprite.getRotation()-90) * (3.14159265358979323846 / 180.0f);
        sf::Vector2f direction = sf::Vector2f(std::cos(radians), std::sin(radians));

		// Create a bullet and add it to the list of bullets
		Bullet* bullet = new Bullet(game, bulletTexture, this->GetSprite().getPosition()+ direction*10.f, direction * 400.f);
        game.entitiesToAdd.push_back(bullet);
        shootTimer = 0.5f;

        if (spreadShotTimer > 0)
        {
            radians += 0.785398f; // 45 degrees in radians
            direction = sf::Vector2f(std::cos(radians), std::sin(radians));
            Bullet* bullet = new Bullet(game, bulletTexture, this->GetSprite().getPosition() + direction * 10.f, direction * 400.f);
            game.entitiesToAdd.push_back(bullet);

            radians -= 1.5708f; // 90 degrees in radians
            direction = sf::Vector2f(std::cos(radians), std::sin(radians));
            Bullet* bullet2 = new Bullet(game, bulletTexture, this->GetSprite().getPosition() + direction * 10.f, direction * 400.f);
            game.entitiesToAdd.push_back(bullet2);
        }
        else if (multiShotTimer > 0)
        {
            for (int i = 0; i < 3; i++)
            {
                radians += 1.5708f; // 90 degrees in radians
                direction = sf::Vector2f(std::cos(radians), std::sin(radians));
                Bullet* bullet = new Bullet(game, bulletTexture, this->GetSprite().getPosition() + direction * 10.f, direction * 400.f);
                game.entitiesToAdd.push_back(bullet);
            }
             
        }

	}

    // Flash when invincible
    if (invincibilityTimer > 0)
    {
        if (invisibleTimer < 0)
        {
            visible = !visible;
            invisibleTimer = 0.25f;
        }
	}
    else
    {
        visible = true;
	}

    shootTimer -= deltaTime;
    invincibilityTimer -= deltaTime;
    invisibleTimer -= deltaTime;
    spreadShotTimer -= deltaTime;
    multiShotTimer -= deltaTime;
}

void Player::OnCollision(GameObject& other)
{
    if (dynamic_cast<Asteroid*>(&other) != nullptr)
    {
        if (invincibilityTimer < 0)
        {
            lives--;
            sprite.setPosition(sf::Vector2f(game.window.getSize().x / 2, game.window.getSize().y / 2));
            invincibilityTimer = 3.f;

            if (lives <= 0)
            {
                game.gameOver = true;
                dead = true;

            }
        }
    }
}

bool Player::CollidesWith(const GameObject& other) const
{
    // If other is an asteroid or powerup, check for collision
    return (dynamic_cast<const Asteroid*>(&other) != nullptr || dynamic_cast<const Powerup*> (&other) != nullptr);
}
