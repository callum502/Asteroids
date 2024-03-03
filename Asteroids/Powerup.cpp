#include "Powerup.h"
#include "Player.h"
#include "Game.h"

Powerup::Powerup(Game& game_, const sf::Texture& tex) : GameObject(game_)
{
	sprite.setTexture(tex);
	sprite.setPosition(rand() % game.window.getSize().x, rand() % game.window.getSize().y);
	sprite.setScale(1.f, 1.0f);

	type = static_cast<PowerupType>(rand() % 3);

	// Set colour based on type
	switch (type)
	{
	case(PowerupType::MultiShot):
			sprite.setColor(sf::Color::Green);
			break;
	case(PowerupType::SpreadShot):
		sprite.setColor(sf::Color::Red);
		break;
	case(PowerupType::Invincibility):
		sprite.setColor(sf::Color::Yellow);
		break;
	default:
		break;
	}
}

void Powerup::OnCollision(GameObject& other)
{
	if (dynamic_cast<Player*>(&other) != nullptr)
	{
		// Apply powerup
		switch (type)
		{
		case(PowerupType::MultiShot):
			game.player->multiShotTimer = 10;
			game.player->spreadShotTimer = 0;
			break;
		case(PowerupType::SpreadShot):
			game.player->spreadShotTimer = 10;
			game.player->multiShotTimer = 0;
			break;
		case(PowerupType::Invincibility):
			game.player->invincibilityTimer = 10;
			break;
		default:
			break;
		}

		// Delete powerup
		dead = true;
	}
}

void Powerup::Update(float deltaTime)
{
	// Delete powerup after duration, flash for last 3 seconds
	if (duration <= 0)
		dead = true;
	if (duration <= 3.f)
	{
		if (invisibleTimer < 0)
		{
			visible = !visible;
			invisibleTimer = 0.25f;
		}
	}

	duration -= deltaTime;
	invisibleTimer -= deltaTime;
}
