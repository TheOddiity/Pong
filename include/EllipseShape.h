#ifndef ELLIPSESHAPE_H
#define ELLIPSESHAPE_H

#include <SFML/Graphics.hpp>


class EllipseShape : public sf::Shape
{
    public:
        EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0));

        sf::Vector2f getRadius() { return m_radius; }
        void setRadius(sf::Vector2f radius) {m_radius = radius; update();}
        sf::Vector2f getPointTangent(std::size_t index) const;

        //sf::Vector2f getSize() {return m_radius;}
        virtual std::size_t getPointCount() const;
        virtual sf::Vector2f getPoint(std::size_t index) const;

        virtual ~EllipseShape();

    protected:
		sf::Vector2f m_radius;
    private:
        
};

#endif // ELLIPSESHAPE_H
