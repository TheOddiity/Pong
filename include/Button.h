#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"

class Button : public sf::Drawable
{
public:
  Button(std::string caption = "", sf::Vector2i windowSize = sf::Vector2i(700, 400));
  ~Button();

  bool update(float dt, const sf::RenderWindow& window);
  void setPosition(const sf::Vector2f& pos);
  void setPosition(float x, float y);
  sf::Vector2f getPosition() const;
  void setFont(const sf::Font& font);
  void setString(const std::string& caption);
  std::string getString() const;
  void setWindowSize(const sf::Vector2i& windowSize);
  void setSize(const sf::Vector2f& size);
  sf::Vector2f getSize() const;

protected:


  sf::RoundedRectangleShape m_button;
  const std::string m_caption;
  sf::Vector2i m_windowSize;
  sf::Vector2f m_pos;
  sf::Vector2f m_size;
  sf::Text m_text;

  float time;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::FloatRect getGlobalNarrowBounds();
};

#endif // BUTTON.H
