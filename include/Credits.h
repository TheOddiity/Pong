#ifndef CREDITS_H
#define CREDITS_H

#include <SFML/Graphics.hpp>
#include <array>

class Credits : public sf::Drawable
{
public:
	Credits(sf::Vector2i windowSize);
	
	bool update();
	
private:
	sf::Vector2i m_windowSize;
	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;
	
	sf::Font m_font;
	mutable sf::Text m_text;
	
	std::string m_left[5];
	std::string m_right[5];
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};

#endif // CREDITS_H