#pragma once

#include <cstdint>
#include <map>
#include <regex>
#include <tuple>

#include "../HTTP/Request.h"
#include "../HTTP/Response.h"
#include "../Sockets/AsyncSocketServer.h"

// HTTP Server implementation over AsyncSocketServer
class HTTPServer
{
public:
	using ViewFunc = std::function<HTTP::Response(HTTP::Request)>;
	using Handler = std::tuple<std::regex, ViewFunc>;

	HTTPServer(std::uint16_t port);
	
	void add_handler(std::string path, ViewFunc handler);

	void listen_forever();

private:
	std::uint16_t m_port;
	std::unique_ptr<AsyncSocketServer> m_server;
	std::vector<Handler> m_handlers;

	void socket_handler(Socket& s);
};
