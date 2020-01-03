#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    sf::Vector2i windowSize{700, 400};
    sf::RenderWindow window{sf::VideoMode(windowSize.x, windowSize.y), "Ping! Pong!"};
    sf::Clock gameTime;
    Game game{windowSize};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        game.update(gameTime.restart().asSeconds());

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}

