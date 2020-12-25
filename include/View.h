#ifndef VIEW_H
#define VIEW_H

class View : public sf::Drawable
{
public:
  virtual bool update(float dt) = 0;
  virtual void reset() {};

protected:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


#endif // VIEW_H
