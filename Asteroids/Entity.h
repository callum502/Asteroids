#pragma once
#include <SFML/Graphics.hpp>

class Game;
class Entity
{
public:
	Entity(Game& game_);
	virtual void Update(float deltaTime) {}
	bool dead = false;
	Game& game;
};

