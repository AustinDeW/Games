#include "Paddle.h"

Paddle::Paddle()
	:paddle(sf::Vector2f(20,100))
{
	paddle.setFillColor(sf::Color::Green);
}

Paddle::~Paddle()
{
}

const sf::Vector2f* Paddle::GetPosition()
{
	return &paddle.getPosition();
}

void Paddle::SetPosition(sf::Vector2f pos)
{
	paddle.setPosition(pos);
}

const sf::Vector2f* Paddle::GetSize()
{
	return &paddle.getSize();
}

const sf::FloatRect Paddle::GetGlobalBounds()
{
	return paddle.getGlobalBounds();
}

void Paddle::Move(sf::Vector2f velocity)
{
	paddle.move(velocity);
}

sf::RectangleShape* Paddle::GetDrawable()
{
	return &paddle;
}
