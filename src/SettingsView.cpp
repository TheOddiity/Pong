#include "SettingsView.h"
#include "sfex.h"
#include "main.h"

#include <iostream>

SettingsView::SettingsView(const sf::Vector2i& windowSize, sf::Font& font, Settings& settings) 
	: m_windowSize{windowSize}, m_font{font}, settings{settings},
				m_toWhatBox{Textbox(font)}
{	
  int textSize{20};
	
  m_title.setString("Settings");
  m_title.setFont(m_font);
  m_title.setCharacterSize(m_windowSize.y * .2f);
  m_title.setPosition((m_windowSize.x - m_title.getLocalBounds().width) / 2, m_windowSize.y * .02f); 
	

  m_toWhatText.setString("Points to win:");
  m_toWhatText.setFont(m_font);
  m_toWhatText.setCharacterSize(textSize);
  m_toWhatText.setPosition(windowSize.x / 2 - 10 - m_toWhatText.getLocalBounds().width,
			   windowSize.y * .4f + (m_toWhatText.getLocalBounds().height -
						 m_toWhatText.getLocalBounds().top) / 2);

  m_toWhatBox.setCharType("#");
  m_toWhatBox.setCharLimit(2);
  m_toWhatBox.setPosition(windowSize.x / 2 + 10,
			  windowSize.y * .4f + (m_toWhatText.getLocalBounds().height -
						m_toWhatText.getLocalBounds().top) / 2);
  m_toWhatBox.setSize(80.f, 25.f);

  m_soundText.setString("Sound:");
  m_soundText.setFont(m_font);
  m_soundText.setCharacterSize(textSize);
  m_soundText.setPosition(windowSize.x / 2 - 10 - m_soundText.getLocalBounds().width,
			  windowSize.y * .4f + (m_soundText.getLocalBounds().height -
						m_soundText.getLocalBounds().top) / 2 * 8);
  m_soundCheckbox.setPosition(windowSize.x / 2 + 10,
			      windowSize.y * .4f + (m_soundText.getLocalBounds().height -
						    m_soundText.getLocalBounds().top) / 2 * 8);
  m_soundCheckbox.setSize(25.f, 25.f);

  m_saveBut.setFont(m_font);
  m_saveBut.setPosition(windowSize.x / 2 + 40, windowSize.y * .8f);
  m_saveBut.setString("OK");
	
  m_cancelBut.setFont(m_font);
  m_cancelBut.setPosition(windowSize.x / 2 - m_saveBut.getSize().x - 40, windowSize.y * .8f);
  m_cancelBut.setString("Cancel");
	
  reset();
}

bool SettingsView::update(float dt, const sf::RenderWindow& window)
{
  if (m_saveBut.update(dt, window))
  {
    settings.points = std::stoi(m_toWhatBox.getString());
    settings.sound = m_soundCheckbox.isChecked();
    return true;
  }
  else if (m_cancelBut.update(dt, window))
  {
    reset();
    return true;
  }
  m_soundCheckbox.update(dt, window);
	    
  return false;
}

void SettingsView::updateText(const sf::Event& event)
{
  m_toWhatBox.updateText(event);
}

void SettingsView::reset()
{
  m_toWhatBox.setString(std::to_string(settings.points));
  m_soundCheckbox.setChecked(settings.sound);
}

void SettingsView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_title);
  target.draw(m_toWhatText);
  target.draw(m_toWhatBox);
  target.draw(m_soundText);
  target.draw(m_soundCheckbox);
  target.draw(m_saveBut);
  target.draw(m_cancelBut);	
}
