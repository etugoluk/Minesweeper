#include "../GUI/GUI.hpp"
#include "../Logic/Logic.hpp"
#include "../inc/Exception.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw BadArguments();

		int size = std::stoi(argv[1]);

		if (size < 5 || size > 25)
			throw BadArguments();

		Logic game(size);
		GUI gui(size);
		gui.execute(game);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}