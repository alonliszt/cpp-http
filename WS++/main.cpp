#include <iostream>

#include "Common.h"
#include "Sockets/WSA.h"

int main()
{
	_WSA::get_main();

	std::cout << std::format("Hello % world!", 5) << std::endl;

	std::bytes x;
}
