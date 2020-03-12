#include <iostream>

#include "Common.h"
#include "Sockets/AsyncSocketServer.h"

#include "HTTP/Request.h"
#include "HTTP/Response.h"

class ConsoleWriter : public ITextWriter
{
public:
	void write(std::bytes b) override
	{
		std::string s(b.begin(), b.end());
		std::cout << s;
	}
};

void handle_socket(Socket& socket)
{
	try
	{
		auto [reader, writer] = socket.create_io();

		HTTP::Request req(reader);
		std::cout << "A request to " << req.path << std::endl;

		HTTP::Response res;
		res.set_body("Hello, world!");

		res.write(writer);
	}
	catch (HTTP::ErrorCode & err)
	{
		std::cout << "HTTP/1.1 " << err.status() << " " << err.to_string() << std::endl;
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
