#include "Game.h"

#include <iostream>
#include <random>
#include <chrono>

#include "sfex.h"

Game::Game(sf::Vector2i windowSize)
    : m_ball{Ball(windowSize, sf::Vector2f(10, 10), 300, Game::randDirectionVector())},
      m_racketRight{Racket(sf::Vector2f(10.f, 40.f),
                        sf::Vector2f(windowSize.x - 20, windowSize.y / 2 - 20), "assets/pingRacket.png")},
      m_racketLeft{Racket(sf::Vector2f(10.f, 40.f),
                        sf::Vector2f(20, windowSize.y / 2 - 20), "assets/pongRacket.png")},
      m_windowSize{windowSize}
{
    restart();
    // Point score
    if(!m_font.loadFromFile("assets/AnotherRound.otf"))
    {
        std::cout << "Error loading font";
    }
    m_pointsLeft = 0;
    m_pointsRight = 0;
    m_pointsLeftText.setFont(m_font);
    m_pointsLeftText.setString("0");
    m_pointsLeftText.setFillColor(sf::Color::Red);
    m_pointsLeftText.setPosition(sf::Vector2f(3, 3));
    m_pointsLeftText.setCharacterSize(20);

    m_pointsRightText = m_pointsLeftText;
    m_pointsRightText.setOrigin(m_pointsRightText.getLocalBounds().width, 0);
    m_pointsRightText.setPosition(sf::Vector2f(windowSize.x - 3, 3));


    /*
     *  Sound
     */
    if (!pingBuffer.loadFromFile("assets/ping.ogg") || !pongBuffer.loadFromFile("assets/pong.ogg"))
    {
        std::cout << "Error loading sounds";
    }
    pingSound.setBuffer(pingBuffer);
    pongSound.setBuffer(pongBuffer);

    srand (static_cast<unsigned> (time(0)));

    m_racketLeft.getPointTangent(4);
}
Game::~Game()
{
    //dtor
}

void Game::update(float dt)
{
    //Logic and input handling
    static bool hitRacket{false};
    checkKeyPressed(dt);

    if (hitRacket)
    {
        hitRacket = false;
    }
    else
    {
        if (m_ball.hitRacket(m_racketRight))
        {
            pongSound.play();
            hitRacket = true;
        }
        else if (m_ball.hitRacket(m_racketLeft))
        {
            pingSound.play();
            hitRacket = true;
        }
    }

    switch(m_ball.move(dt))
    {
    case -1:
        ++m_pointsLeft;
        m_pointsLeftText.setString(std::to_string(m_pointsLeft));
        restart();
        break;
    case 1:
        ++m_pointsRight;
        m_pointsRightText.setString(std::to_string(m_pointsRight));
        m_pointsRightText.setOrigin(m_pointsRightText.getLocalBounds().width, 0);
        restart();
        break;
    default:
        break;
    }
}

void Game::checkKeyPressed(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            && m_racketRight.getPosition().y - m_racketRight.getRadius().y > 0)
    {
        m_racketRight.move(sf::Vector2f(0.f, -dt));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            && m_racketRight.getPosition().y + m_racketRight.getRadius().y < m_windowSize.y)
    {
        m_racketRight.move(sf::Vector2f(0.f, dt));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            && m_racketLeft.getPosition().y - m_racketLeft.getRadius().y > 0)
    {
        m_racketLeft.move(sf::Vector2f(0.f, -dt));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            && m_racketLeft.getPosition().y + m_racketLeft.getRadius().y < m_windowSize.y)
    {
        m_racketLeft.move(sf::Vector2f(0.f, dt));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        restart();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        pause();
        pointIndex++;
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //draw everything
    target.draw(m_ball);
    target.draw(m_racketLeft);
    target.draw(m_racketRight);
//    sfex::drawPoints(target, &m_racketLeft);
//    sfex::drawPoints(target, &m_racketRight);
    target.draw(m_pointsLeftText);
    target.draw(m_pointsRightText);
    //target.draw(m_ellipse);

//    static int i = 0;
//    if (i >= m_racketLeft.getPointCount())
//        i = 0;

//    sfex::drawPoint(target, m_racketLeft.getGlobalPoint(0), sf::Color::Red);

    sf::VertexArray line{sf::Lines, 2};

    line[0].position = m_racketLeft.getGlobalPoint(pointIndex) + m_racketLeft.getPointTangent(pointIndex) * 50.f;
    line[1].position = m_racketLeft.getGlobalPoint(pointIndex) + m_racketLeft.getPointTangent(pointIndex) * -50.f;
    //m_racketLeft.getGlobalPoint(i);//m_ball.getPosition().x < m_windowSize.x / 2
                        //? m_racketLeft.getGlobalPoint(i) : m_racketRight.getGlobalPoint(i++));
//    sfex::drawPoint(target, line[0].position, sf::Color::Green);
//    sfex::drawPoint(target, line[1].position, sf::Color::Green);

    //target.draw(line);
//    ++i;
}

void Game::restart()
{
    m_ball.setPosition(m_windowSize.x / 2, m_windowSize.y / 2);
    m_ball.setDirection(randDirectionVector());
    m_racketLeft.setSpeed();
    m_racketRight.setSpeed();
    m_pause = false;
}

sf::Vector2f Game::randDirectionVector()
{
    static std::default_random_engine generator{static_cast<long unsigned int>(time(0))};
    static std::normal_distribution<float> dist(0.f, 1.f);

    float x = static_cast<float> (rand()) / RAND_MAX;
    float y = dist(generator);

    //std::cout << "Game::randDirectionVector: " << x << ", " << y << '\n';
    //return sf::Vector2f(1, 0);
    return sfex::norm(sf::Vector2f((x < 0.5 ? -1 : 1), y));
}

void Game::pause()
{
    m_ball.setDirection(0, 0);
    m_racketLeft.setSpeed(0);
    m_racketRight.setSpeed(0);
    m_pause = true;
}

