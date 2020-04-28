#include "MenuView.h"

#include <iostream>
#include "sfex.h"

MenuView::MenuView(const sf::Vector2i& windowSize, sf::Font& font) : m_windowSize{windowSize}, m_buttonFont{font}
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
	
	int numButs{4};
	std::string bNameList[] = {"Play", "Settings", "Credits", "Exit"};
	//buttons = new std::vector<MenuButton>(numButs);
	buttons.reserve(numButs);
	for (int i = 0; i < numButs; ++i)
	{
		buttons.push_back(MenuButton(bNameList[i], windowSize));
		buttons.back().setFont(m_buttonFont);
		buttons.back().setPosition();
	}	
}

MenuView::ButtonList MenuView::update(float dt, const sf::RenderWindow& window)
{
	for(MenuButton& b : buttons)
	{
		if (b.update(dt, window))
			return static_cast<MenuView::ButtonList>(b.getIndex());
	}
	
	return NUM_BUTTONS;
}

void MenuView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_bgSprite);	
	target.draw(m_logoSprite);
	target.draw(m_titleSprite);
	for (const MenuButton& b : buttons)
	{
		target.draw(b);
	}
}

MenuView::~MenuView()
{
	//dtor
}
