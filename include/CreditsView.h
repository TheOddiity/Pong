#ifndef CREDITSVIEW_H
#define CREDITSVIEW_H

#include <SFML/Graphics.hpp>
#include <array>

class CreditsView : public sf::Drawable
{
public:
	CreditsView(const sf::Vector2i& windowSize, sf::Font& font);
	
	bool update();
	
private:
	sf::Vector2i m_windowSize;
	float lineSpacing;
	sf::Font m_font;
	
	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;
	
	sf::Texture m_SFMLTexture;
	sf::Sprite m_SFMLSprite;
	
	mutable sf::Text m_text;
	sf::Text m_thanksText;
	
	std::array<std::string, 5> m_left;
	std::array<std::string, 5> m_right;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};

#endif // CREDITSVIEW_H
