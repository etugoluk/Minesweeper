#include "GUI.hpp"
#include "Logic.hpp"
#include <unistd.h>

int main()
{
	int size = 5;

	Logic game(size);

	GUI gui(size);
	gui.execute(game);

	sleep(3);
	return 0;
}