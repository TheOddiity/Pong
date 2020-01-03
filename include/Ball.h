#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

#include "Racket.h"

class Ball : public sf::CircleShape
{
public:
    Ball(sf::Vector2i windowSize, sf::Vector2f startPos, double speed, sf::Vector2f direction);

    int move(float dt);
    bool hitRacket(Racket& racket);
    bool contains(sf::Vector2f point);
    void setDirection(float x, float y);
    void setDirection(sf::Vector2f direction);

    virtual ~Ball();

protected:

private:
    static float m_rad;
    sf::Vector2i m_windowSize;
    double m_speed;
    sf::Vector2f m_direction;


};

#endif // BALL_H
