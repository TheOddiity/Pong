#include "Menu.h"

#include <iostream>
#include "sfex.h"

Menu::Menu(sf::Vector2i windowSize) : m_windowSize{windowSize}
{
	if (!m_bgTexture.loadFromFile("assets/menuBG.png"))
	{
		std::cout << "Error loading background image";
	}
	m_bgSprite.setTexture(m_bgTexture);
	
	if (!m_logoTexture.loadFromFile("assets/logo.png"))
	{
		std::cout << "Error loading logo";
	}
	m_logoSprite.setTexture(m_logoTexture);
	
	float scaleFactor{80.f / m_logoTexture.getSize().y};
	m_logoSprite.scale(scaleFactor, scaleFactor);
	m_logoSprite.setPosition(10, m_windowSize.y - m_logoTexture.getSize().y * scaleFactor);
	
	if (!m_titleTexture.loadFromFile("assets/title.png"))
	{
		std::cout << "Error loading title image";
	}
	m_titleSprite.setTexture(m_titleTexture);
	scaleFactor = 120.f / m_titleTexture.getSize().y;
	m_titleSprite.scale(scaleFactor, scaleFactor);
	m_titleSprite.setPosition((windowSize.x - m_titleTexture.getSize().x * scaleFactor) / 2, windowSize.y * .05);
	
	if(!m_buttonFont.loadFromFile("assets/PermanentMarker-Regular.ttf"))
	{
		std::cout << "Error loading the font";
	}
		  
	
	int numButs{4};
	std::string bNameList[] = {"Play", "Settings", "Credits", "Exit"};
	//buttons.resize(numButs);
	for (int i = 0; i < numButs; ++i)
	{
		buttons.push_back(Button(bNameList[i], windowSize));
		buttons.back().setFont(m_buttonFont);
	}
	
	
}

Menu::ButtonList Menu::update(float dt, const sf::RenderWindow& window)
{
	for(Button& b : buttons)
	{
		if (b.update(dt, window))
			return static_cast<Menu::ButtonList>(b.getIndex());
	}
	
	return NUM_BUTTONS;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_bgSprite);	
	target.draw(m_logoSprite);
	target.draw(m_titleSprite);
	for (Button b : buttons)
	{
		target.draw(b);
	}
}

Menu::~Menu()
{
	//dtor
}
