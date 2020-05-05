#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Ball.h"
#include "Racket.h"
#include "EllipseShape.h"
#include "Settings.h"

class GameView : public sf::Drawable
{
public:
	enum class Side
	{
		LEFT,
		NONE,
		RIGHT
	};
	
    GameView(const sf::Vector2i& windowSize, sf::Font& font, Settings& settings);
    ~GameView();

    bool update(float dt);
	void reset();

protected:


private:
    Ball m_ball;
    Racket m_racketRight;
    Racket m_racketLeft;
    EllipseShape m_ellipse;
    sf::Vector2i m_windowSize;
    sf::Font m_font;
    Settings& settings;

    bool m_pause{false};
	bool m_gameOver{false};

    //Test
    int pointIndex{0};

    int m_pointsLeft;
    int m_pointsRight;

    sf::Text m_pointsLeftText;
    sf::Text m_pointsRightText;
	sf::Text m_fpsText;
	sf::Text m_gameOverText;
	sf::Text m_playerWinsText;
	sf::Text m_startText;
	sf::Text m_pauseText;
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

    void stop();

    static sf::Vector2f randSpeedVector();
};

#endif // GAMEVIEW_H
