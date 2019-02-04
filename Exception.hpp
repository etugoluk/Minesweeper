#pragma once

#include <stdexcept>

class BadArguments : public std::exception
{
	public:
		const char *what() const throw();	
};