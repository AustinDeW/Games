#pragma once
#include <SFML\Graphics.hpp>
class Ball
{
	public:
	Ball();
	~Ball();

	const sf::Vector2f* GetPosition();
	const float GetRadius();
	const sf::FloatRect GetGlobalBounds();
	sf::CircleShape* GetDrawable();

	void SetPosition(sf::Vector2f pos);
	void Move(sf::Vector2f velocity);

	private:
	sf::CircleShape ball;

};

