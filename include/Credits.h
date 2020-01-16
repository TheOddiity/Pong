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
	
	sf::Texture m_SFMLTexture;
	sf::Sprite m_SFMLSprite;
	
	sf::Font m_font;
	mutable sf::Text m_text;
	float lineSpacing;
	sf::Text m_thanksText;
	
	std::array<std::string, 5> m_left;
	std::array<std::string, 5> m_right;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};

#endif // CREDITS_H