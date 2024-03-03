#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(Game& game, const sf::Texture& texture, sf::Vector2f position, sf::Vector2f velocity_) : GameObject(game)
{
	sprite.setScale(0.5f, 0.5f);
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 0, 0));
	sprite.setPosition(position);
	velocity = velocity_;
}

void Bullet::Update(const float deltaTime)
{
	sprite.move(velocity * deltaTime);

	//mark as dead if it goes off screen
	if (sprite.getPosition().x < 0 || sprite.getPosition().x > game.window.getSize().x || sprite.getPosition().y < 0 || sprite.getPosition().y > game.window.getSize().y)
		dead = true;
}
