#include "Racket.h"

// For Test
#include <iostream>
#include "sfex.h"

Racket::Racket(sf::Vector2f position, std::string texturePath, sf::Vector2f size) : EllipseShape(size), m_speed{200}
{
    if (!m_texture.loadFromFile(texturePath))
    {
        std::cout << "Error loading texture";
    }
	m_sprite.setTexture(m_texture);
    // * 2 for getting from radius to diameter
	m_sprite.setScale(size.x * 2 / m_texture.getSize().x, size.y * 2 / m_texture.getSize().y);
    m_sprite.setOrigin(getOrigin() * 2.f);
	setPosition(position);
}

sf::Vector2f Racket::getGlobalPoint(const std::size_t index) const
{
    return getPosition() + getPoint(index) - getOrigin();
}

float Racket::getSpeed()
{
    return m_speed;
}

void Racket::setPosition(const sf::Vector2f& pos)
{
	EllipseShape::setPosition(pos);
	m_sprite.setPosition(pos);
}


void Racket::move(const sf::Vector2f& offset)
{
    EllipseShape::move(offset * m_speed);
	m_sprite.move(offset * m_speed);
}

void Racket::setSpeed(float speed)
{
    m_speed = speed;
}

void Racket::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_sprite);
}

Racket::~Racket()
{
    //dtor
}
