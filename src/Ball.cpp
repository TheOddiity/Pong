#include "Ball.h"

#include <iostream>
#include "sfex.h"

float Ball::m_rad = 10.f;

Ball::Ball(sf::Vector2i windowSize, sf::Vector2f startPos, double speed, sf::Vector2f direction)
    : sf::CircleShape(m_rad), m_windowSize{windowSize}, m_speed{speed},
      m_direction{sfex::norm(direction)}
{
    setFillColor(sf::Color::Green);
    setOrigin(m_rad, m_rad);
    setPosition(startPos.x, startPos.y);
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

    if (getPosition().y >= m_windowSize.y - m_rad && m_direction.y > 0)
    {
        m_direction.y *= -1;
    }
    else if (getPosition().y <= m_rad && m_direction.y < 0)
    {
        m_direction.y *= -1;
    }

    sf::CircleShape::move(m_direction.x * m_speed * dt,
                          m_direction.y * m_speed * dt);

    return 0;

}

sf::Vector2f Ball::hitRacket(Racket& racket) const
{
    if (m_direction == sf::Vector2f(0, 0))
        return sf::Vector2f(0, 0);

    if (getGlobalBounds().intersects(racket.getGlobalBounds()))
    {
        for (int i = 0; i < racket.getPointCount(); ++i)
        {
            if (sfex::length(getPosition() - racket.getGlobalPoint(i)) <= m_rad)
            {
                return racket.getPointTangent(static_cast<size_t>(i));
            }

        }
    }

    return sf::Vector2f(0, 0);
}

void Ball::setDirection(float x, float y)
{
    setDirection(sf::Vector2f(x, y));
}

void Ball::setDirection(const sf::Vector2f& direction)
{
    m_direction = direction;
}

sf::Vector2f Ball::getDirection() const
{
	return m_direction;
}

Ball::~Ball()
{
    //dtor
}
