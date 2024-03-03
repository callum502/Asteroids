#pragma once
#include <SFML/Graphics.hpp>

class Game;

class UI
{
public:
	UI(Game& game);
	void Render();

private:
	sf::Font font;
	Game& game;
};

