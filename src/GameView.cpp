#include "GameView.h"

#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

#include "sfex.h"
#include "main.h"

GameView::GameView(const sf::Vector2i& windowSize, sf::Font& font, Settings& settings)
    : m_ball{Ball(windowSize, GameView::randSpeedVector())},
      m_racketRight{sf::Vector2f(windowSize.x - 20, windowSize.y / 2 - 20), "assets/pingRacket.png"},
      m_racketLeft{sf::Vector2f(20, windowSize.y / 2 - 20), "assets/pongRacket.png"},
      m_windowSize{windowSize}, m_font{font}, settings{settings}
{
	srand (static_cast<unsigned> (time(0)));

    restart();
    // Point score

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

    m_fpsText.setFont(m_font);
    m_fpsText.setFillColor(sf::Color::White);
    m_fpsText.setCharacterSize(15);
    m_fpsText.setPosition(windowSize.x, windowSize.y);

    m_startText.setFont(m_font);
    setStartString();


    /*
     *  Sound
     */
    if (!pingBuffer.loadFromFile("assets/ping.ogg") || !pongBuffer.loadFromFile("assets/pong.ogg"))
    {
        std::cout << "Error loading sounds";
    }
    pingSound.setBuffer(pingBuffer);
    pongSound.setBuffer(pongBuffer);

    m_pauseText.setFont(m_font);
    m_pauseText.setString("Paused");
    m_pauseText.setCharacterSize(static_cast<unsigned int>(m_windowSize.y * 0.2));
    m_pauseText.setPosition((m_windowSize.x - m_pauseText.getLocalBounds().width) / 2,
                            (m_windowSize.y - m_pauseText.getLocalBounds().height) / 2
			    - m_pauseText.getLocalBounds().top);
}
GameView::~GameView()
{
    //dtor
}

bool GameView::update(float dt)
{
	static bool spacePressed{false};
	if (!spacePressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_pause = !m_pause;
		spacePressed = true;
	}
	else if(spacePressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		spacePressed = false;
	}

	if(!hasFocus || m_pause)
		return false;

    //Logic and input handling
    if(m_countdown < 4 && (m_countdown += dt) > 1)
	{
		m_startText.setCharacterSize(static_cast<unsigned int>(m_windowSize.y * .5));
		m_startText.setString(std::to_string(static_cast<int>(5 - m_countdown)));
		m_startText.setPosition((m_windowSize.x - m_startText.getLocalBounds().width) / 2,
								(m_windowSize.y - m_startText.getLocalBounds().height) / 2
							     -  m_startText.getLocalBounds().top);
		return false;
	}

    checkKeyPressed(dt);

	checkCollision();

    moveBall(dt);

	m_fpsText.setString(std::to_string(static_cast<int>(1/dt)));
	m_fpsText.setOrigin(m_fpsText.getLocalBounds().width + 3, m_fpsText.getLocalBounds().height + 3);

	if (m_pointsRight >= settings.points || m_pointsLeft >= settings.points)
	{
		gameOver();
	}

	if (m_gameOver)
	{
		if((m_gameOverTimer += dt) > 3)
		{
			if(sfex::anyKeyPressed())
				return true;
		}
		else
		{
			m_gameOverTextSize += 15 * dt;
			gameOverSetSize();
		}
	}

	return false;
}

void GameView::checkKeyPressed(float dt)
{
	sf::Vector2f mvLeft(0, 0);
	sf::Vector2f mvRight(0, 0);

	// Left and Right for Left player

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
	   		&& m_racketLeft.getPosition().x - m_racketLeft.getRadius().x > 10)
	{
		mvLeft.x = -1;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			&& m_racketLeft.getPosition().x + m_racketLeft.getRadius().x < m_windowSize.x /2 - 15)
	{
		mvLeft.x = 1;
	}

	// Up and down for Left player

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            && m_racketLeft.getPosition().y - m_racketLeft.getRadius().y > 0)
    {
		mvLeft.y = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            && m_racketLeft.getPosition().y + m_racketLeft.getRadius().y < m_windowSize.y)
    {
        mvLeft.y = 1;
    }

	// Left and right for Right player

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
	   		&& m_racketRight.getPosition().x - m_racketRight.getRadius().x > m_windowSize.x / 2 + 15)
	{
		mvRight.x = -1;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			&& m_racketRight.getPosition().x + m_racketRight.getRadius().x < m_windowSize.x - 10)
	{
		mvRight.x  = 1;
	}

	// Up and down for Right player

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            && m_racketRight.getPosition().y - m_racketRight.getRadius().y > 0)
    {
		mvRight.y = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            && m_racketRight.getPosition().y + m_racketRight.getRadius().y < m_windowSize.y)
    {
		mvRight.y = 1;
    }

	m_racketLeft.move(sfex::norm(mvLeft) * dt);
	m_racketRight.move(sfex::norm(mvRight) * dt);

	sf::Vector2f diffPos;
	switch (checkCollision())
	{
		case Side::LEFT:
			m_ball.increaseSpeed(sfex::norm(mvLeft) * 100.f);
			diffPos = m_ball.getPosition() - m_racketLeft.getPosition();
			if(mvLeft.x * diffPos.x > 0)
			{
				m_ball.move(sfex::norm(mvLeft) * m_racketLeft.getSpeed() * dt);
			}
			break;
		case Side::RIGHT:
			m_ball.increaseSpeed(sfex::norm(mvRight) * 100.f);
			diffPos = m_ball.getPosition() - m_racketRight.getPosition();
			if(mvRight.x * diffPos.x > 0)
			{
				m_ball.move(sfex::norm(mvRight) * m_racketRight.getSpeed() * dt);
			}
			break;
		case Side::NONE:
			break;
	}
}

GameView::Side GameView::checkCollision()
{

  static bool hitRight{false};
  static bool hitLeft{false};
  sf::Vector2f hitVector{m_ball.hitRacket(m_racketRight)};
  if (hitVector != sf::Vector2f(0,0))
  {
    if (!hitRight) // true when ball left right rackets space
    {
      if (settings.sound)
	pongSound.play();

      hitRight = true;
      m_ball.setSpeed(sfex::reflect(m_ball.getSpeed(), hitVector));
      return Side::RIGHT;
    }
  }
  else
  {
    hitRight = false;
  }

  hitVector = m_ball.hitRacket(m_racketLeft);
  if (hitVector != sf::Vector2f(0,0))
  {
    if (!hitLeft) // true when ball left left rackets space
    {
      if (settings.sound)
	pingSound.play();
      hitLeft = true;
      m_ball.setSpeed(sfex::reflect(m_ball.getSpeed(), hitVector));
      return Side::LEFT;
    }
  }
  else
  {
    hitLeft = false;
  }

  return Side::NONE;
}

void GameView::moveBall(float dt)
{
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

void GameView::reset()
{
	m_pointsLeft = 0;
	m_pointsRight = 0;
    m_pointsLeftText.setString("0");
    m_pointsLeftText.setString("0");
	m_racketLeft.setPosition(sf::Vector2f(20, m_windowSize.y / 2 - 20));
	m_racketRight.setPosition(sf::Vector2f(m_windowSize.x - 20, m_windowSize.y / 2 - 20));
	m_gameOver = false;
	m_gameOverTimer = 0;
	restart();
	setStartString();
}

void GameView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //draw everything
	target.draw(m_fpsText);
    target.draw(m_racketLeft);
    target.draw(m_racketRight);
    target.draw(m_pointsLeftText);
    target.draw(m_pointsRightText);

	if (m_countdown < 4)
	{
		target.draw(m_startText);
	}
	else if (m_gameOver)
	{
		target.draw(m_gameOverText);
		target.draw(m_playerWinsText);
	}
	else
	{
		target.draw(m_ball);
		if(m_pause || !hasFocus)
			target.draw(m_pauseText);
	}
}

void GameView::restart()
{
    m_ball.setPosition(m_windowSize.x / 2, m_windowSize.y / 2);
    m_ball.setSpeed(randSpeedVector());
    m_racketLeft.setSpeed();
    m_racketRight.setSpeed();
    m_pause = false;
}

void GameView::setStartString()
{
	m_startText.setString("Get Ready!");
	m_startText.setCharacterSize(static_cast<unsigned int>(m_windowSize.y * 0.2));
	m_startText.setPosition((m_windowSize.x - m_startText.getLocalBounds().width) / 2,
							(m_windowSize.y - m_startText.getLocalBounds().height) / 2
						   	 -  m_startText.getLocalBounds().top);
	m_countdown = 0;
}

void GameView::gameOver()
{
	stop();
	m_gameOver = true;
	m_gameOverTextSize = 50.f;
	m_gameOverText.setString("Game Over");
	m_gameOverText.setFont(m_font);
	//m_gameOverText.setFillColor(sf::Color(200, 200, 200));

	m_playerWinsText.setString(std::string(m_pointsLeft > m_pointsRight ? "Blue" : "Red") + " wins!");
	m_playerWinsText.setFont(m_font);
	m_playerWinsText.setFillColor(m_pointsLeft > m_pointsRight ? sf::Color(100, 210, 210) : sf::Color(255, 100, 100));

	gameOverSetSize();


	m_racketLeft.setPosition(sf::Vector2f(80, 70));
	m_racketRight.setPosition(sf::Vector2f(620, 310));

	m_pointsRight = m_pointsLeft = 0;
}

void GameView::gameOverSetSize()
{
	m_gameOverText.setCharacterSize(static_cast<unsigned int>(m_gameOverTextSize));
	m_gameOverText.setPosition((m_windowSize.x - m_gameOverText.getLocalBounds().width) / 2,
							   (m_windowSize.y - m_gameOverText.getLocalBounds().height) * .3);
	m_playerWinsText.setCharacterSize(static_cast<unsigned int>(m_gameOverTextSize * .7f));
	m_playerWinsText.setPosition((m_windowSize.x - m_playerWinsText.getLocalBounds().width) / 2,
							     m_gameOverText.getPosition().y + m_gameOverTextSize * 1.5);
}

sf::Vector2f GameView::randSpeedVector()
{
    static std::default_random_engine generator{static_cast<long unsigned int>(time(0))};
    static std::normal_distribution<float> dist(0.f, 1.f);

    float x = static_cast<float> (rand()) / RAND_MAX;
    float y = dist(generator);

    return sfex::norm(sf::Vector2f((x < 0.5 ? -1 : 1), y)) * 200.f;
}

void GameView::stop()
{
    m_ball.setSpeed(0, 0);
    m_racketLeft.setSpeed(0);
    m_racketRight.setSpeed(0);
}

