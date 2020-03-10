#include <iostream>

#include "Common.h"
#include "Sockets/AsyncSocketServer.h"

#include "HTTP/HTTPRequest.h"

void handle_socket(Socket& socket)
{
	try
	{
		auto [reader, writer] = socket.create_io();

		HTTP::Request req(reader);
		std::cout << "A request to " << req.path << std::endl;

		std::string line;
		while ((line = reader.readline()).size() > 0)
		{
			std::cout << line << std::endl;
		}

		std::cout << "============= END OF REQUEST ===============" << std::endl;
	}
	catch (HTTP::Error & err)
	{
		std::cout << "HTTP error: " << err.what() << std::endl;
	}
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
