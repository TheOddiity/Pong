#include "AdventureView.h"

AdventureView::AdventureView(const sf::Vector2i& windowSize, sf::Font& font, Settings& settings)
  :  r_windowSize{windowSize}, r_font{font}, r_settings{settings},
     m_heroRacket{sf::Vector2f(50, windowSize.y * 0.1), "assets/pongRacket.png", sf::Vector2f(40.f, 10.f)},
     m_ball{Ball(windowSize, sf::Vector2f(1.f, 1.f))}
{ }

bool AdventureView::update(float dt)
{
  return false;
}

void AdventureView::reset() {}

void AdventureView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_heroRacket);
  target.draw(m_ball);
}
