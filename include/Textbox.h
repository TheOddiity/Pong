#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"

class Textbox : public sf::Drawable
{
public:
	Textbox(const sf::Font& font, const sf::Vector2f& size = sf::Vector2f(80, 20), const sf::Vector2f& pos = sf::Vector2f(0.f, 0.f));
	Textbox();
	
	void setSize(const sf::Vector2f& size);
	void setSize(float x, float y);
	sf::Vector2f getSize() const;
	void setPosition(const sf::Vector2f& pos);
	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;
	void setFocus(bool hasFocus);
	bool hasFocus() const;
	void setCharType(std::string type);
	std::string getCharType() const;
	void setCharLimit(int limit);
	int getCharLimit() const;
	void setString(std::string text);
	std::string getString() const;
	void setOrigin(sf::Vector2f origin);
	sf::Vector2f getOrigin() const;
	
	
	void updateText(const sf::Event& event);
	
private:
	sf::RoundedRectangleShape m_rrShape;
	sf::Vector2f m_size;
	sf::Vector2f m_pos;
	sf::Vector2f m_origin;
	
	sf::Text m_text;
	
	int m_charLim;
	std::string m_charType;
	
	bool m_hasFocus{false};
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void setStringOrigin();
	bool acceptChar(char c);
};

#endif //TEXTBOX_H