#include "EllipseShape.h"
#include <cmath>

#include "sfex.h"

EllipseShape::EllipseShape(const sf::Vector2f& radius)
    : m_radius{radius}
{
    setOrigin(radius);
    update();
}


std::size_t EllipseShape::getPointCount() const
{
    return 30;
}

sf::Vector2f EllipseShape::getPoint(std::size_t index) const
{
    static const float pi = 3.1415926535f;

    float angle = index * 2 * pi / getPointCount() - pi / 2;
    float x = std::cos(angle) * m_radius.x;
    float y = std::sin(angle) * m_radius.y;

    return sf::Vector2f(m_radius.x + x, m_radius.y + y);
}

sf::Vector2f EllipseShape::getPointTangent(std::size_t index) const
{
    sf::Vector2f point{getPoint(index) - getOrigin()};
    return sfex::norm(sf::Vector2f (-point.y * std::pow(m_radius.x, 2), point.x * std::pow(m_radius.y, 2)));
}


EllipseShape::~EllipseShape()
{
    //dtor
}
