#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Ball.h"
#include "Racket.h"
#include "EllipseShape.h"

class Game : public sf::Drawable
{
public:
    Game(sf::Vector2i windowSize = sf::Vector2i(200, 200));
    ~Game();

    void update(float dt);
    void checkKeyPressed(float dt);

protected:


private:
    Ball m_ball;
    Racket m_racketRight;
    Racket m_racketLeft;
    EllipseShape m_ellipse;
    sf::Vector2i m_windowSize;

    bool m_pause{false};

    //Test
    int pointIndex{0};

    int m_pointsLeft;
    int m_pointsRight;

    sf::Font m_font;
    sf::Text m_pointsLeftText;
    sf::Text m_pointsRightText;

    sf::SoundBuffer pingBuffer;
    sf::SoundBuffer pongBuffer;
    sf::Sound pingSound;
    sf::Sound pongSound;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void restart();

    void pause();

    static sf::Vector2f randDirectionVector();
};

#endif // GAME_H
