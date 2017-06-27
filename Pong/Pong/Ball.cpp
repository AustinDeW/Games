#include "Ball.h"

Ball::Ball()
	:ball(15,15)
{
	ball.setFillColor(sf::Color::Green);
}

Ball::~Ball()
{
}

const sf::Vector2f* Ball::GetPosition()
{
	return &ball.getPosition();
}

const float Ball::GetRadius()
{
	return ball.getRadius();
}

const sf::FloatRect Ball::GetGlobalBounds()
{
	return ball.getGlobalBounds();
}

sf::CircleShape* Ball::GetDrawable()
{
	return &ball;
}

void Ball::SetPosition(sf::Vector2f pos)
{
	ball.setPosition(pos);
}

void Ball::Move(sf::Vector2f velocity)
{
	ball.move(velocity);
}
