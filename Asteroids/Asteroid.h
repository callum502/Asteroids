#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class AsteroidManager;

enum class AsteroidSize
{
	Small,
	Medium,
	Large
};

class Asteroid : public GameObject
{
public:
    Asteroid(Game& game, AsteroidManager& asteroidManager_, const sf::Texture& texture, sf::Vector2f position, sf::Vector2f velocity_, float rotationSpeed_, sf::Vector2f scale);
    void Update(const float deltaTime) override;
    void OnCollision(GameObject& other) override;

private:
    void Split();
    sf::Vector2f velocity;
    float rotationSpeed = 20.f;
    AsteroidSize size = AsteroidSize::Large;
    AsteroidManager& asteroidManager;
};
