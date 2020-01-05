#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RoundedRectangleShape.hpp>

class Button : public sf::Drawable
{
public: 
	Button(std::string caption = "", sf::Vector2i windowSize = sf::Vector2i(700, 400));
	~Button();
	
	bool update(float dt, const sf::RenderWindow& window);
	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() const;
	void setFont(const sf::Font& font);
	int getIndex() const;
	
protected:

private:
	sf::RoundedRectangleShape m_button;
	const std::string m_caption;
	sf::Vector2i m_windowSize;
	
	sf::Text m_text;

	const sf::Color Color_outline;
	const sf::Color Color_fill;
	const sf::Color Color_hover;
	const sf::Color Color_text;
	
	const int buttonNumber;
	static int s_buttonNumber;
	
	float time;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::FloatRect getGlobalNarrowBounds();
};

#endif // BUTTON.H