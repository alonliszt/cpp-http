#include <iostream>

#include "Common.h"

#include "HTTPServer/HTTPServer.h"

int main()
{
	try
	{
		HTTPServer server(8080);
		server.add_handler("/hello", [](HTTP::Request req) -> HTTP::Response {
			std::cout << "Received request!" << std::endl;
			
			HTTP::Response res(200, "OK");
			res.set_body(
				std::format("You are sending the request from: %", req.headers["User-Agent"])
			);

			return res;
		});
		server.listen_forever();
	}
	catch (Socket::Error & err)
	{
		std::cout << err.what() << std::endl;
	}
}
