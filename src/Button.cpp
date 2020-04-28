#include "Button.h"

#include <iostream>
#include "sfex.h"

Button::Button(std::string caption, sf::Vector2i windowSize) : 
			m_button{sf::RoundedRectangleShape(sf::Vector2f(100, 30), 10, 8)}, 
			m_caption{caption}, m_windowSize{windowSize},
			Color_fill{sf::Color(180, 180, 180, 0)}, // Grey
			Color_outline{sf::Color(200, 200, 200)}, // Dark red
			Color_hover{sf::Color(255, 255, 255, 40)}, // Light Grey
			Color_text{sf::Color(0, 166, 0)}
{
	m_button.setOutlineThickness(5);
	m_button.setOutlineColor(Color_outline);
	m_button.setFillColor(Color_fill);
	
	m_text.setString(caption);
	m_text.setFillColor(Color_text);
	m_text.setCharacterSize(static_cast<int>(m_button.getSize().y * .7));
	
	m_size = sf::Vector2f(100, 30);
}

bool Button::update(float dt, const sf::RenderWindow& window)
{
	if (getGlobalNarrowBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
	{
		if (sfex::mouseButtonReleased(sf::Mouse::Left))
			return true;
		m_button.setFillColor(Color_hover);
	}
	else
	{
		m_button.setFillColor(Color_fill);
	}
	
	return false;
	
}

void Button::setPosition(const sf::Vector2f& pos)
{
	m_pos = pos;
	m_button.setPosition(pos);
	m_text.setPosition(pos - sf::Vector2f(0, m_text.getLocalBounds().top / 1.f) 
					   + (m_button.getSize() - sf::Vector2f(m_text.getLocalBounds().width, 
														  m_text.getLocalBounds().height)) / 2.f);
}
void Button::setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }
sf::Vector2f Button::getPosition() const { return m_pos; }
	

void Button::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void Button::setString(const std::string& caption)
{
	m_text.setString(caption);
	setPosition(m_pos);
}

void Button::setWindowSize(const sf::Vector2i& windowSize) { m_windowSize = windowSize; }

void Button::setSize(const sf::Vector2f& size)
{
	m_size = size;
	m_button.setSize(size);
	m_button.setCornersRadius(size.y / 10.f);
	m_text.setCharacterSize(static_cast<int>(m_button.getSize().y * .7));
	m_text.setPosition(m_pos - sf::Vector2f(0, m_text.getLocalBounds().top / 1.f) 
					   + (m_button.getSize() - sf::Vector2f(m_text.getLocalBounds().width, 
														  m_text.getLocalBounds().height)) / 2.f);
}
sf::Vector2f Button::getSize() const { return m_size; }


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_button);
	target.draw(m_text);
}

sf::FloatRect Button::getGlobalNarrowBounds()
{
	return sf::FloatRect(m_button.getPosition().x, m_button.getPosition().y, m_button.getSize().x, m_button.getSize().y);
}
	

Button::~Button()
{}