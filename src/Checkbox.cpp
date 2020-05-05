#include "Checkbox.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "sfex.h"
#include "Colors.h"

Checkbox::Checkbox(sf::Vector2f position, sf::Vector2f size) :
  m_pos{position}, m_size{size},
  m_box{sf::RoundedRectangleShape(size, size.x / 4.f, 8)}
{
  m_box.setPosition(m_pos);
  m_box.setOutlineThickness(3);
  m_box.setCornerPointCount(8);
  m_box.setOutlineColor(Colors::TextboxBorder);
  m_box.setFillColor(Colors::TextboxFill);

  m_checked = true;

  setCross();
}

void Checkbox::update(float dt, const sf::RenderWindow& window)
{
  if (getGlobalNarrowBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
  {
    if (sfex::mouseButtonReleased(sf::Mouse::Left))
    {
      toggleChecked();
    }

    //m_box.setFillColor(HoverColor);
  }
  else
  {
    //m_box.setFillColor(FillColor);
  }
}     

void Checkbox::setPosition(const sf::Vector2f& pos)
{
  m_pos = pos;
  m_box.setPosition(pos);
  setCross();
}
void Checkbox::setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }
sf::Vector2f Checkbox::getPosition() const { return m_pos; }

void Checkbox::setSize(const sf::Vector2f& size)
{
  m_size = size;
  m_box.setSize(size);
  setCross();
}
void Checkbox::setSize(float x, float y) { setSize(sf::Vector2f(x, y)); }
sf::Vector2f Checkbox::getSize() const { return m_size; }

void Checkbox::setChecked(bool checked) { m_checked = checked; }
void Checkbox::toggleChecked() { m_checked = !m_checked; }
bool Checkbox::isChecked() const { return m_checked; }


void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_box);

  if (m_checked)
  {
    target.draw(m_cross1);
    target.draw(m_cross2);
  }    
}

 sf::FloatRect Checkbox::getGlobalNarrowBounds() const
{
  return sf::FloatRect(m_box.getPosition().x, m_box.getPosition().y,
			     m_box.getSize().x, m_box.getSize().y);
}

void Checkbox::setCross()
{
  float thicknessRatio = 0.1f;
  float smallestDimention = (m_size.x > m_size.y ? m_size.y : m_size.x);
  float barThickness = smallestDimention * thicknessRatio;

  // Rotational angle in radians tan-1(width / height)
  float alpha = atan(m_size.x / m_size.y);
  
  // To make sure it starts within the box (sin(alpha) * barThickness)
  float positionOffset = sin(alpha) * barThickness;

  // Length offset so cross is within the box bounds (tan(90-alpha) * barThickness / 2)
  float lengthOffset = tan(M_PI / 2 - alpha) * barThickness;
  
  m_cross1.setSize(sf::Vector2f(sfex::length(m_size) - lengthOffset,
				smallestDimention * thicknessRatio));
  m_cross1.setPosition(m_pos + sf::Vector2f(positionOffset, 0));
  m_cross1.setRotation(45);

  m_cross2.setSize(sf::Vector2f(sfex::length(m_size) - lengthOffset,
				smallestDimention * thicknessRatio));
  m_cross2.setPosition(m_pos + sf::Vector2f(0, m_size.y - barThickness + positionOffset));
  m_cross2.setRotation(-45);
}
