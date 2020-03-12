#include <iostream>

#include "Common.h"

#include "HTTPServer/HTTPServer.h"

HTTP::Response index(HTTP::Request req)
{
	std::cout << "Received request!" << std::endl;

	return HTTP::Response(HTTP::OK{
		std::format("You are sending the request from: %", req.headers["User-Agent"])
	});
}

int main()
{
	try
	{
		HTTP::Server server(8080);
		server.add_handler("/", index);
		server.listen_forever();
	}
	catch (Socket::Error & err)
	{
		std::cout << err.what() << std::endl;
	}
}
