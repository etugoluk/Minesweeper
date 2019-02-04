#include "GUI.hpp"
#include "Logic.hpp"
#include <unistd.h>

int main()
{
	Logic game(10);
	GUI gui;

	gui.execute(game);
	sleep(3);

	return 0;
}