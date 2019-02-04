#include "Exception.hpp"

const char* BadArguments::what() const throw()
{
	return ("Usage: ./minesweeper [map_size]\n[map_size] - from 5 to 25");
}