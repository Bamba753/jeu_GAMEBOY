#include "Game.hpp"

int main()
{
	// init time
	std::srand(time(NULL));
	// Window
	Game game;

	// Game loop
	while (game.running() && !game.endGameState())
	{


		// Update
		game.update();

		// Render
		game.render();
	}

	return 0;
}