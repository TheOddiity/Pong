#include "Credits.h"
#include "sfex.h"

#include <iostream>

Credits::Credits(sf::Vector2i windowSize) : m_windowSize{windowSize}, 
					m_left{ "Head Game Developer"	, "Assistant Game Developer", "", "Head Graphics Designer"	, "Head Audio Guy"	},
					m_right{"TheOddity"				, "TheOddity"				, "", "TheOddity"				, "TheOddity"		} 	
{
	if(!m_logoTexture.loadFromFile("assets/logo.png"))
	{
		std::cout << "Error loading Credits::Logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	float scale{windowSize.y * .25f / m_logoTexture.getSize().y};
	m_logoSprite.scale(scale, scale);
	m_logoSprite.setPosition((windowSize.x - m_logoTexture.getSize().x * scale) / 2, windowSize.y * 0.05f);
	
	if(!m_font.loadFromFile("assets/PermanentMarker-Regular.ttf"))
	{
		std::cout << "Error loading Credits::Font" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(static_cast<unsigned int>(windowSize.y * .05f));
}

bool Credits::update()
{
	return sfex::anyKeyPressed();
}

void Credits::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_logoSprite);

	for(int i = 0; i < 5; ++i)
	{
		m_text.setString(m_left[i]);
		m_text.setPosition(m_windowSize.x / 2.f - m_text.getLocalBounds().width - 20, 
						   m_windowSize.y * .4f + i * m_text.getCharacterSize() * 1.8f);
		target.draw(m_text);
	}
	
	for(int i = 0; i < 5; ++i)
	{
		m_text.setString(m_right[i]);
		m_text.setPosition(m_windowSize.x / 2.f + 20, 
						   m_windowSize.y * .4f + i * m_text.getCharacterSize() * 1.8f);
		target.draw(m_text);
	}
}