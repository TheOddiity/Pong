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
	enum class Side
	{
		LEFT,
		NONE,
		RIGHT
	};
	
    Game(const sf::Vector2i& windowSize);
    ~Game();

    bool update(float dt);
	void reset();

protected:


private:
    Ball m_ball;
    Racket m_racketRight;
    Racket m_racketLeft;
    EllipseShape m_ellipse;
    sf::Vector2i m_windowSize;
	int m_winningScore;

    bool m_pause{false};
	bool m_gameOver{false};

    //Test
    int pointIndex{0};

    int m_pointsLeft;
    int m_pointsRight;

    sf::Font m_font;
    sf::Text m_pointsLeftText;
    sf::Text m_pointsRightText;
	sf::Text m_fpsText;
	sf::Text m_gameOverText;
	sf::Text m_playerWinsText;
	sf::Text m_startText;
	float m_countdown;
	float m_gameOverTextSize;
	float m_gameOverTimer;
	
    sf::SoundBuffer pingBuffer;
    sf::SoundBuffer pongBuffer;
    sf::Sound pingSound;
    sf::Sound pongSound;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    void checkKeyPressed(float dt);
	Side checkCollision();
	void moveBall(float dt);
	void restart();
	void setStartString();
	void gameOver();
	void gameOverSetSize();

    void pause();

    static sf::Vector2f randSpeedVector();
};

#endif // GAME_H
