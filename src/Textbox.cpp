#include "Textbox.h"

#include <iostream>
#include <string>

#include "sfex.h"

Textbox::Textbox(const sf::Font& font, const sf::Vector2f& size, const sf::Vector2f& pos) 
				: Textbox()
{
	m_rrShape.setSize(size);
	m_rrShape.setCornersRadius(size.y / 4.f);
	
	m_text.setFont(font);
	
	
	setSize(size);
	setPosition(pos);
}

Textbox::Textbox()
{
	
	m_rrShape.setCornerPointCount(8);
	m_rrShape.setOutlineThickness(3);
	m_rrShape.setOutlineColor(sf::Color::Red);
	m_rrShape.setFillColor(sf::Color::Blue);
	
	m_text.setFillColor(sf::Color::White);
	m_text.setOutlineColor(sf::Color::White);
	m_text.setString("10");
	
	m_charLim = 15;
	m_charType = "*";	
	
	m_hasFocus = true;
}
	
void Textbox::setSize(const sf::Vector2f& size)
{
	m_size = size;
	
	m_text.setCharacterSize(static_cast<unsigned int>(size.y * 0.8));
	m_rrShape.setSize(size);
	m_rrShape.setCornersRadius(size.y / 4);
	m_text.setPosition(m_pos - m_origin + m_size / 2.f);	
	setStringOrigin();
}
void Textbox::setSize(float x, float y)
{
	setSize(sf::Vector2f(x, y));
}
sf::Vector2f Textbox::getSize() const { return m_size; }

void Textbox::setPosition(const sf::Vector2f& pos)
{
	m_pos = pos;
	m_rrShape.setPosition(pos);

	setStringOrigin();
	m_text.setPosition(pos - m_origin + m_size / 2.f);	
}
void Textbox::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}
sf::Vector2f Textbox::getPosition() const { return m_pos; }

void Textbox::setFocus(bool hasFocus) { m_hasFocus = hasFocus; }
bool Textbox::hasFocus() const { return m_hasFocus; }

void Textbox::setCharType(std::string type) { m_charType = type; }
std::string Textbox::getCharType() const { return m_charType; }

void Textbox::setCharLimit(int limit) { m_charLim = limit; }
int Textbox::getCharLimit() const { return m_charLim; }

void Textbox::setString(std::string text) 
{ 
	m_text.setString(text); 
	m_text.setPosition(m_pos - m_origin + m_size / 2.f);	
}
std::string Textbox::getString() const { return m_text.getString(); }

void Textbox::setOrigin(sf::Vector2f origin) 
{ 
	m_origin = origin; 
	m_rrShape.setOrigin(origin);
	m_text.setPosition(m_pos - origin + m_size / 2.f);
}
sf::Vector2f Textbox::getOrigin() const { return m_origin; }

void Textbox::updateText(const sf::Event& event)
{
	if(event.type == sf::Event::TextEntered && event.text.unicode == '\b')
	{
		m_text.setString(m_text.getString().substring(0, m_text.getString().getSize() - 1));
		setStringOrigin();
	}
	else if(event.type == sf::Event::TextEntered)
	{
		if (m_text.getString().getSize() >= m_charLim || !acceptChar(static_cast<char>(event.text.unicode)))
		{
			return;
		}
		m_text.setString(m_text.getString() + static_cast<char>(event.text.unicode));
		setStringOrigin();
	}
						 
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_rrShape);
	target.draw(m_text);
}

void Textbox::setStringOrigin()
{
	sf::FloatRect tRect{m_text.getLocalBounds()};
	m_text.setOrigin(tRect.width / 2.f + tRect.left, tRect.height / 2.f + tRect.top);
}

bool Textbox::acceptChar(char c)
{
	if (m_charType.find("*") != std::string::npos)
	{
		return true;
	}
	if (m_charType.find("#") != std::string::npos && isdigit(c))
	{
		return true;
	}
	if (m_charType.find(c) != std::string::npos)
	{
		return true;
	}
	return false;
}
