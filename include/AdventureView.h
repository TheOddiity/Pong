#ifndef ADVENTUREVIEW_H
#define ADVENTUREVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "View.h"
#include "Ball.h"
#include "Racket.h"
#include "Settings.h"

class AdventureView : public View
{
public:
  AdventureView(const sf::Vector2i& windowSize, sf::Font& font, Settings& settings);

  bool update(float dt) override;
  void reset() override;

protected:
  sf::Vector2i r_windowSize;
  sf::Font& r_font;
  Settings& r_settings;

  Racket m_heroRacket;
  Ball m_ball;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // ADVENTUREVIEW_H
