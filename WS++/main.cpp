#include <iostream>

#include "Common.h"
#include "Sockets/SocketServer.h"

int main()
{
	try
	{
		SocketServer server;
		auto socket = server.accept();
		auto [reader, writer] = socket.create_io();
		std::cout << reader.readline() << std::endl;
		writer.write_str("Thanks for the info :)");
	}
	catch (Socket::Error & err)
	{
		std::cout << err.what() << std::endl;
	}
}
