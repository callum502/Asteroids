#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player(Game& game_);
    void Update(const float deltaTime) override;
    void OnCollision(GameObject& other) override;

    int lives = 3;
    float invincibilityTimer = 0.f;
    float multiShotTimer = 0;
    float spreadShotTimer = 0;

private:
    void Initialize();
    bool CollidesWith(const GameObject& other) const override;

    float movementSpeed = 200.f;
    float rotationSpeed = 180.f;
    float shootTimer = 0.f;
    float invisibleTimer = 0.f;
    sf::Texture bulletTexture;
};