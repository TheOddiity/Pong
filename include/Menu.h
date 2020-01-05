#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"


class Menu : public sf::Drawable
{
public:
	enum ButtonList{
		PLAY,
		SETTINGS,
		CREDITS,
		EXIT,
		NUM_BUTTONS
	};
	Menu(sf::Vector2i windowSize = sf::Vector2i(700, 400));
	~Menu();
	ButtonList update(float dt, const sf::RenderWindow& window);

protected:

private:
	sf::Vector2i m_windowSize;
	
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;
	
	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;
	
	sf::Texture m_titleTexture;
	sf::Sprite m_titleSprite;
	
	std::vector<Button> buttons;
	sf::Font m_buttonFont;
	
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	

};

#endif //MENU.H