#include "Game.h"

int main()
{
	Game game(sf::VideoMode(800, 600), "Pong");
	while (game.GetWindow()->isOpen())
	{
		if (game.mainMenuOpen)
		{
			game.MainMenu();
		}
		else
		{
			game.HandleInput();
			game.Update();
			game.Render();
		}
	}
	return 0;
}