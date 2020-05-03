#include <SFML/Graphics.hpp>

#include "main.h"
#include "MenuView.h"
#include "GameView.h"
#include "SettingsView.h"
#include "CreditsView.h"

#include "Settings.h"

#include <iostream>


enum class GameState
{
	MENU,
	PLAY,
	SETTINGS,
	CREDITS
};

bool hasFocus{false};

int main()
{
    sf::Vector2i windowSize{700, 400};
    sf::RenderWindow window{sf::VideoMode(windowSize.x, windowSize.y), "Ping? Pong!"};
    sf::Clock gameTime;
	
	GameState state{GameState::MENU};
	sf::Font font;
	if(!font.loadFromFile("assets/PermanentMarker-Regular.ttf"))
	{
		
	}
	
	Settings settings{15};
	
	MenuView menuView{windowSize, font};
	GameView gameView{windowSize, font, settings};
	SettingsView settingsView{windowSize, font, settings};
	CreditsView creditsView{windowSize, font};

	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}
			else if (event.type == sf::Event::GainedFocus)
			{
				hasFocus = true;
			}
			else if (event.type == sf::Event::LostFocus)
			{
				hasFocus = false;
			}
			else if (state == GameState::SETTINGS)
			{
				settingsView.updateText(event);
			}
			
		
		
		}

		switch (state)
		{
			case GameState::MENU:
				switch (menuView.update(gameTime.restart().asSeconds(), window))
				{
					case MenuView::PLAY:
						state = GameState::PLAY;
						gameView.reset();
						break;
					case MenuView::SETTINGS:
						state = GameState::SETTINGS;
						break;
					case MenuView::CREDITS:
						state = GameState::CREDITS;
						break;
					case MenuView::EXIT:
						window.close();
						break;
				}
				break;
			case GameState::PLAY:
				if (gameView.update(gameTime.restart().asSeconds()))
					state = GameState::MENU;
				break;
			case GameState::SETTINGS:
				if (settingsView.update(gameTime.restart().asSeconds(), window))
					state = GameState::MENU;
				break;
			case GameState::CREDITS:
				if(creditsView.update())
					state = GameState::MENU;
				break;
		}
		

        window.clear();
		switch (state)
		{
			case GameState::MENU:
				window.draw(menuView);
				break;
			case GameState::PLAY:
				window.draw(gameView);
				break;
			case GameState::SETTINGS:
				window.draw(settingsView);
				break;
			case GameState::CREDITS:
				window.draw(creditsView);
				break;
		}
        window.display();
    }

    return 0;
}

