#include "Settings.h"
#include "sfex.h"

Settings::Settings(sf::Vector2i windowSize) : m_windowSize{windowSize}
{
	
}

bool Settings::update()
{
	return sfex::anyKeyPressed();
}

void Settings::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}