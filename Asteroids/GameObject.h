#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class GameObject : public Entity 
{
public:
	GameObject(Game& game_);

	sf::Sprite& GetSprite() { return sprite; }
	const sf::Sprite& GetSprite() const { return sprite; }
	bool TestCollision(const GameObject& other);
	virtual void OnCollision(GameObject& other) {}
	virtual void Draw();
	void SetVisible(bool visible_) { visible = visible_; }

protected:
	sf::Sprite sprite;
	sf::Texture texture;
	bool visible = true;

	// Override to control which entities this entity can collide with
	virtual bool CollidesWith(const GameObject& other) const { return true; }
};

