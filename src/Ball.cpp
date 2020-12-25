#include "Ball.h"

#include <iostream>
#include "sfex.h"

const float Ball::m_rad = 10.f;

Ball::Ball(sf::Vector2i windowSize, sf::Vector2f speed, sf::Vector2f startPos)
    : sf::CircleShape(m_rad), m_windowSize{windowSize}, m_speed{speed}
{
    setFillColor(sf::Color::Green);
    setOrigin(m_rad, m_rad);

	if (startPos == sf::Vector2f(0.f, 0.f)) // no startPos sent
	{
		setPosition(windowSize.x / 2, windowSize.y / 2);
	}
	else
	{
    	setPosition(startPos.x, startPos.y);
	}
}

int Ball::move(float dt)
{
    if (getPosition().x  + m_rad >= m_windowSize.x)
    {
        return -1;
    }
    else if (getPosition().x - m_rad <= 0)
    {
        return 1;
    }

    if (getPosition().y >= m_windowSize.y - m_rad && m_speed.y > 0)
    {
        m_speed.y *= -1;
    }
    else if (getPosition().y <= m_rad && m_speed.y < 0)
    {
        m_speed.y *= -1;
    }

    sf::CircleShape::move(m_speed * dt);

    return 0;
}

int Ball::move(const sf::Vector2f& offset)
{
	if (getPosition().x  + m_rad >= m_windowSize.x)
    {
        return -1;
    }
    else if (getPosition().x - m_rad <= 0)
    {
        return 1;
    }

    if (getPosition().y >= m_windowSize.y - m_rad && m_speed.y > 0)
    {
        m_speed.y *= -1;
    }
    else if (getPosition().y <= m_rad && m_speed.y < 0)
    {
        m_speed.y *= -1;
    }

    sf::CircleShape::move(offset);

    return 0;
}

sf::Vector2f Ball::hitRacket(Racket& racket) const
{
    if (m_speed == sf::Vector2f(0, 0))
        return sf::Vector2f(0, 0);

    if (getGlobalBounds().intersects(racket.getGlobalBounds()))
    {
        for (unsigned int i = 0; i < racket.getPointCount(); ++i)
        {
            if (sfex::length(getPosition() - racket.getGlobalPoint(i)) <= m_rad)
            {
                return racket.getPointTangent(static_cast<size_t>(i));
            }

        }
    }

    return sf::Vector2f(0, 0);
}

sf::Vector2f Ball::getSpeed() const
{
	return m_speed;
}

void Ball::setSpeed(float x, float y)
{
	m_speed.x = x;
	m_speed.y = y;
}

void Ball::setSpeed(const sf::Vector2f& speed)
{
	m_speed = speed;
}

void Ball::increaseSpeed(const sf::Vector2f& inc)
{
	m_speed += inc;
}

Ball::~Ball()
{
    //dtor
}
