#include "Racket.h"

// For Test
#include <iostream>
#include "sfex.h"

Racket::Racket(sf::Vector2f size, sf::Vector2f position, std::string texturePath) : EllipseShape(size), m_speed{200}
{
    setPosition(position);
	
	/*
     *  Texture and Sprite
     */
    if (!texture.loadFromFile(texturePath))
    {
        std::cout << "Error loading texture";
    }
    sprite.setOrigin(getOrigin());
	sprite.setTexture(texture);
    sprite.setPosition(position - m_radius / 2.f);
	sprite.setScale(size.x * 2 / texture.getSize().x, size.y * 2 / texture.getSize().y);
}

sf::Vector2f Racket::getGlobalPoint(const std::size_t index) const
{
    return getPosition() + getPoint(index) - getOrigin();
}

float Racket::getSpeed() 
{
    return m_speed;
}

void Racket::move(const sf::Vector2f& offset) 
{
    EllipseShape::move(offset * m_speed);
	sprite.move(offset * m_speed);
}

void Racket::setSpeed(float speed)
{
    m_speed = speed;
}

void Racket::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(sprite);	
//	sfex::drawPoints(target, this);
//	sfex::drawPoint(target, getOrigin(), sf::Color::Black);
}
Racket::~Racket()
{
    //dtor
}
