#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

class Settings : public sf::Drawable
{
public:
	Settings(sf::Vector2i windowSize);
	
	bool update();
	
private:
	sf::Vector2i m_windowSize;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // SETTINGS_H