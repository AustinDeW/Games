#pragma once
#include <SFML\Graphics.hpp>
class Paddle
{
	public:
	Paddle();
	~Paddle();

	const sf::Vector2f* GetPosition();
	const sf::Vector2f* GetSize();
	const sf::FloatRect GetGlobalBounds();
	sf::RectangleShape* GetDrawable();

	void SetPosition(sf::Vector2f pos);
	void Move(sf::Vector2f velocity);

	private:
	sf::RectangleShape paddle;
};

