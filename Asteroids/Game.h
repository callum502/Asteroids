#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Entity;
class Player;
class Bullet;
class AsteroidManager;
class PowerupManager;
class UI;

class Game 
{
public:
    Game();
    void Run();
    std::vector<Entity*> entities;
    std::vector<Entity*> entitiesToAdd;

    sf::RenderWindow window;
    int score = 0;
    bool gameOver = false;
    Player* player = nullptr;
    void Restart();
private:
    sf::Clock gameClock;
    sf::Music music;

    AsteroidManager* asteroidManager;
    PowerupManager* powerupManager;

    UI* ui;
    void Initialize();
    void HandleEvents();
    void Update();
    void Render();
};