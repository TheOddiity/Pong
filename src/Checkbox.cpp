#include "Checkbox.h"

#include "sfex.h"

Checkbox::Checkbox(sf::Vector2f position, sf::Vector2f size)
{
  m_pos = position;
  m_size = size;
}

void Checkbox::update(const sf::RenderWindow& window)
{
  if (getGlobalNarrowBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
  {
    if (sfex::mouseButtonReleased(sf::Mouse::Left))
      toggleChecked();

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
}
void Checkbox::setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }
sf::Vector2f Checkbox::getPosition() const { return m_pos; }

void Checkbox::setSize(const sf::Vector2f& size)
{
  m_size = size;
  m_box.setSize(size);
}
void Checkbox::setSize(float x, float y) { setSize(sf::Vector2f(x, y)); }
sf::Vector2f Checkbox::getSize() const { return m_size; }

void Checkbox::setChecked(bool checked) { m_checked = checked; }
void Checkbox::toggleChecked() { m_checked = !m_checked; }
bool Checkbox::getChecked() const { return m_checked; }


void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_box);

  if (m_checked)
  {
    //Draw check mark
  }    
}

sf::FloatRect Checkbox::getGlobalNarrowBounds() const
{
	return sf::FloatRect(m_box.getPosition().x, m_box.getPosition().y,
			     m_box.getSize().x, m_box.getSize().y);
}
