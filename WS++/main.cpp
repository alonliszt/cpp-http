#include <iostream>

#include "Common.h"
#include "Sockets/AsyncSocketServer.h"

void handle_socket(Socket& socket)
{
	std::cout << "Connection started " << socket.to_string() << std::endl;

	auto [reader, writer] = socket.create_io();
	std::cout << reader.readline() << std::endl;
	writer.write_str("Thanks for the info :)");
}

int main()
{
	try
	{
		AsyncSocketServer server(8080);
		server.set_handler(handle_socket);
		server.serve_forever();
	}
	catch (Socket::Error & err)
	{
		std::cout << err.what() << std::endl;
	}
}
