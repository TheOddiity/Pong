#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

#include "Racket.h"

class Ball : public sf::CircleShape
{
public:
    Ball(sf::Vector2i windowSize, sf::Vector2f direction, sf::Vector2f startPos = sf::Vector2f(0.f, 0.f));

    int move(float dt);
	int move(const sf::Vector2f& offset);
    sf::Vector2f hitRacket(Racket& racket) const;
    bool contains(const sf::Vector2f& point) const;
	sf::Vector2f getSpeed() const;
	void setSpeed(const sf::Vector2f& speed);
	void setSpeed(float x, float y);
	void increaseSpeed(const sf::Vector2f& inc);

    virtual ~Ball();

protected:

private:
    static const float m_rad;
    sf::Vector2i m_windowSize;
    sf::Vector2f m_speed;


};

#endif // BALL_H
