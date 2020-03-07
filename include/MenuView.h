#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "MenuButton.h"


class MenuView : public sf::Drawable
{
public:
	enum ButtonList{
		PLAY,
		SETTINGS,
		CREDITS,
		EXIT,
		NUM_BUTTONS
	};
	MenuView(const sf::Vector2i& windowSize, sf::Font& font);
	~MenuView();
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
	
	std::vector<MenuButton> buttons;
	sf::Font m_buttonFont;
	
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	

};

#endif //MENUVIEW.H
