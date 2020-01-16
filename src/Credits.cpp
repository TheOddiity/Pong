#include "Credits.h"
#include "sfex.h"

#include <iostream>

Credits::Credits(sf::Vector2i windowSize) : m_windowSize{windowSize}, lineSpacing{1.8f},
					m_left{ "Head Game Developer"		, "Assistant Game Developer", "", "Head Graphics Designer"	, "Head Audio Guy"	},
					m_right{"Odd \"TheOddity\" Restad"	, "Odd \"TheOddity\" Restad", "", "Odd \"TheOddity\" Restad", "Odd \"TheOddity\" Restad"} 	
{
	if(!m_logoTexture.loadFromFile("assets/logo.png"))
	{
		std::cout << "Error loading Credits::Logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	float scale{windowSize.y * .25f / m_logoTexture.getSize().y};
	m_logoSprite.setScale(scale, scale);
	m_logoSprite.setPosition((windowSize.x - m_logoTexture.getSize().x * scale) / 2, windowSize.y * 0.05f);
	
	if(!m_font.loadFromFile("assets/PermanentMarker-Regular.ttf"))
	{
		std::cout << "Error loading Credits::Font" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(static_cast<unsigned int>(windowSize.y * .035f));
	
	if(!m_SFMLTexture.loadFromFile("assets/SFMLLogo.png"))
	{
		std::cout << "Error loading Credits::SFMLLogo";
	}
	m_SFMLSprite.setTexture(m_SFMLTexture);
	scale = windowSize.y * 0.08 / m_SFMLTexture.getSize().y;
	m_SFMLSprite.setScale(scale, scale);
	m_SFMLSprite.setPosition((m_windowSize.x - m_SFMLTexture.getSize().x * scale) / 2, 
							 m_windowSize.y * .35f + (m_right.size() + 2) * m_text.getCharacterSize() * lineSpacing);
	
	m_thanksText.setFont(m_font);
	m_thanksText.setCharacterSize(static_cast<unsigned int>(windowSize.y * .025f));	
	m_thanksText.setString("With special thanks to Overdrivr for the RoundedRectangleShape-Class");
	m_thanksText.setPosition((m_windowSize.x - m_thanksText.getLocalBounds().width) / 2.f,
					   m_windowSize.y * .35f + (m_right.size() + 3) * m_text.getCharacterSize() * lineSpacing + 10);
}

bool Credits::update()
{
	return sfex::anyKeyPressed();
}

void Credits::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(m_logoSprite);

	for(int i = 0; i < m_left.size(); ++i)
	{
		m_text.setString(m_left[i]);
		m_text.setPosition(m_windowSize.x / 2.f - m_text.getLocalBounds().width - 20, 
						   m_windowSize.y * .35f + i * m_text.getCharacterSize() * lineSpacing);
		target.draw(m_text);
	}
	
	for(int i = 0; i < m_right.size(); ++i)
	{
		m_text.setString(m_right[i]);
		m_text.setPosition(m_windowSize.x / 2.f + 20, 
						   m_windowSize.y * .35f + i * m_text.getCharacterSize() * lineSpacing);
		target.draw(m_text);
	}
	
	m_text.setString("Powered by:");
	m_text.setPosition((m_windowSize.x - m_text.getLocalBounds().width) / 2.f,
					   m_windowSize.y * .35f + (m_right.size() + 1) * m_text.getCharacterSize() * lineSpacing);
	target.draw(m_text);
	target.draw(m_SFMLSprite);
	
	target.draw(m_thanksText);
	
}