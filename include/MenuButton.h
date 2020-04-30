#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "Button.h"
#include <SFML/Graphics.hpp>

class MenuButton : public Button
{
public:
	MenuButton(std::string caption = "", sf::Vector2i windowSize = sf::Vector2i(700, 400));
	MenuButton(const MenuButton& old);
	
	int getIndex() const;
	void setPosition();
	using Button::setPosition;
	
private:
	const int c_buttonNumber;
	static int s_buttonNumber;
};

#endif // MENUBUTTON_H