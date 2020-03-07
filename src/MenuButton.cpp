#include "MenuButton.h"

#include <iostream>

int MenuButton::s_buttonNumber{0};

MenuButton::MenuButton(std::string caption, sf::Vector2i windowSize) 
	: Button(caption, windowSize), c_buttonNumber{s_buttonNumber++}
{
	std::cerr << "MenuButton::Menubutton\n";
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
