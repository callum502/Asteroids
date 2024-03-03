#include "UI.h"
#include "Player.h"
#include "Game.h"

UI::UI(Game& game) : game(game)
{
	font.loadFromFile("Assets/arial.ttf");
}

void UI::Render()
{
	//text setup
	sf::Text text;
	text.setCharacterSize(32);
	text.setStyle(sf::Text::Bold);
	text.setFont(font);
	char buffer[256];

	if(!game.gameOver)
	{ 
	// Lives
	sprintf_s(buffer, (sizeof(buffer) / sizeof(buffer[0])), "Lives: %d", game.player->lives);
	text.setString(buffer);
	text.setOrigin(0, 0);
	text.setPosition(game.window.getSize().x * 0.02, game.window.getSize().y * 0.02);
	game.window.draw(text);

	// Score
	sprintf_s(buffer, (sizeof(buffer) / sizeof(buffer[0])), "Score: %d", game.score);
	text.setString(buffer);
	text.setOrigin(0, 0);
	text.setPosition(game.window.getSize().x * 0.02, game.window.getSize().y * 0.02 + 30);
	game.window.draw(text);

	}
	else
	{
		// Game over
		text.setString("Game Over!");
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(game.window.getSize().x * 0.5, game.window.getSize().y * 0.5 - 50);
		game.window.draw(text);

		// Score
		sprintf_s(buffer, (sizeof(buffer) / sizeof(buffer[0])), "Score: %d", game.score);
		text.setString(buffer);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(game.window.getSize().x * 0.5, game.window.getSize().y * 0.5);
		game.window.draw(text);

		// Restart
		text.setString("Press R to restart");
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(game.window.getSize().x * 0.5, game.window.getSize().y * 0.5 + 50);
		game.window.draw(text);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			game.Restart();
		}
	}
}