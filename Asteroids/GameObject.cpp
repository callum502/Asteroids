#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(Game& game_) : Entity(game_)
{
}

bool GameObject::TestCollision(const GameObject& other)
{
	if (CollidesWith(other) && other.CollidesWith(*this))
	{
		const sf::Sprite& a = GetSprite();
		const sf::Sprite& b = other.GetSprite();

		const sf::IntRect boundsA(a.getGlobalBounds());
		const sf::IntRect boundsB(b.getGlobalBounds());
		sf::IntRect intersection;

		if (boundsA.intersects(boundsB, intersection))
			return true;
	}

	return false;
}

void GameObject::Draw()
{
	if (visible)
		game.window.draw(sprite);
}