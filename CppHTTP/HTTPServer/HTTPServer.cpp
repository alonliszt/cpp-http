#include "HTTPServer.h"

HTTP::Server::Server(std::uint16_t port)
	: m_port(port) {}

void HTTP::Server::add_handler(std::string path, ViewFunc handler)
{
	m_handlers.push_back(Handler(std::regex(path), handler));
}

void HTTP::Server::listen_forever()
{
	m_server = std::make_unique<AsyncSocketServer>(m_port);
	m_server->set_handler([this](Socket& s) {
		this->socket_handler(s);
	});
	m_server->serve_forever();
}

void HTTP::Server::socket_handler(Socket& s)
{
	auto [reader, writer] = s.create_io();
	HTTP::Request req(reader);

	for (auto& handler : m_handlers)
	{
		if (std::regex_match(req.path, std::get<0>(handler)))
		{
			HTTP::Response res{ 
				std::get<1>(handler)(std::move(req))
			};

			res.write(writer);

			std::cout << "Reading more" << std::endl;
			reader.readline();
			std::cout << "Finished" << std::endl;
			return;
		}
	}

	HTTP::Response res{ HTTP::NotFound("The resource was not found on the server") };
	res.write(writer);
}
