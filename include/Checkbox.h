#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"

class Checkbox : public sf::Drawable
{

public:

  Checkbox(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(30, 30));

  void update(float dt, const sf::RenderWindow& window);
  
  void setPosition(const sf::Vector2f& pos);
  void setPosition(float x, float y);
  sf::Vector2f getPosition() const;

  void setSize(const sf::Vector2f& size);
  void setSize(float x, float y);
  sf::Vector2f getSize() const;

  void setChecked(bool checked);
  void toggleChecked();
  bool isChecked() const;

protected:
  sf::Vector2f m_pos;
  sf::Vector2f m_size;
  sf::RoundedRectangleShape m_box;
  sf::RectangleShape m_cross1;
  sf::RectangleShape m_cross2;
  

  bool m_checked;


  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::FloatRect getGlobalNarrowBounds() const;
  void setCross();
};

#endif // CHECKBOX_H
