#ifndef RACKET_H
#define RACKET_H

#include <SFML/Graphics.hpp>

#include "EllipseShape.h"


class Racket : public EllipseShape
{
    public:
        Racket(sf::Vector2f size, sf::Vector2f position, std::string texturePath);

        sf::Vector2f getGlobalPoint(const size_t index) const;
        virtual void move(const sf::Vector2f& offset);

        float getSpeed();
        void setSpeed(float speed = 200);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override;

        virtual ~Racket();

    protected:

    private:
        float m_speed;
		
		sf::Texture texture;
		sf::Sprite sprite;
};

#endif // RACKET_H
