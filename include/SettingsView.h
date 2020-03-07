#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "Textbox.h"
#include "Button.h"

class SettingsView : public sf::Drawable
{
public:
	SettingsView(const sf::Vector2i& windowSize, sf::Font& font, Settings settings);
	
	bool update(float dt, const sf::RenderWindow& window);
	void updateText(const sf::Event& event);
	
private:
	Settings settings;
	sf::Vector2i m_windowSize;
	sf::Font m_font;
	sf::Text m_title;
	sf::Text m_toWhatText;
	sf::Text m_IPText;
	
	Textbox m_toWhatBox;
	Textbox m_IPBox;
	
	Button m_saveBut;
	Button m_cancelBut;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // SETTINGSVIEW_H
