#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Game.h"
#include "Settings.h"
#include "Credits.h"


enum class GameState
{
	MENU,
	PLAY,
	SETTINGS,
	CREDITS
};

int main()
{
    sf::Vector2i windowSize{700, 400};
    sf::RenderWindow window{sf::VideoMode(windowSize.x, windowSize.y), "Ping? Pong!"};
    sf::Clock gameTime;
	
	GameState state{GameState::MENU};
	
	Menu menu{windowSize};
	Game game{windowSize};
	Settings settings{windowSize};
	Credits credits{windowSize};
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		switch (state)
		{
			case GameState::MENU:
				switch (menu.update(gameTime.restart().asSeconds(), window))
				{
					case Menu::PLAY:
						state = GameState::PLAY;
						game.reset();
						break;
					case Menu::SETTINGS:
						state = GameState::SETTINGS;
						break;
					case Menu::CREDITS:
						state = GameState::CREDITS;
						break;
					case Menu::EXIT:
						window.close();
						break;
				}
				break;
			case GameState::PLAY:
				if (game.update(gameTime.restart().asSeconds()))
					state = GameState::MENU;
				break;
			case GameState::SETTINGS:
				if (settings.update())
					state = GameState::MENU;
				break;
			case GameState::CREDITS:
				if(credits.update())
					state = GameState::MENU;
				break;
		}
		

		
        window.clear();
		switch (state)
		{
			case GameState::MENU:
				window.draw(menu);
				break;
			case GameState::PLAY:
				window.draw(game);
				break;
			case GameState::SETTINGS:
				window.draw(settings);
				break;
			case GameState::CREDITS:
				window.draw(credits);
				break;
		}
        window.display();
    }

    return 0;
}

