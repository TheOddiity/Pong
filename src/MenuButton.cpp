#include "MenuButton.h"

#include <iostream>

int MenuButton::s_buttonNumber{0};

MenuButton::MenuButton(std::string caption, sf::Vector2i windowSize) 
	: Button(caption, windowSize), c_buttonNumber{s_buttonNumber++}
{
}
MenuButton::MenuButton(const MenuButton& old) : Button(old.m_caption, old.m_windowSize), c_buttonNumber{old.c_buttonNumber}
{
	m_button = old.m_button;
	m_pos = old.m_pos;
	m_size = old.m_size;
	
	m_text = old.m_text;
}
int MenuButton::getIndex() const
{
	return c_buttonNumber;
}

void MenuButton::setPosition()
{
	setPosition(sf::Vector2f((m_windowSize.x - m_button.getSize().x) / 2, 
									   m_windowSize.y * .45 + (m_button.getSize().y + 25) * c_buttonNumber)); 
}
