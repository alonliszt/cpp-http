#include "SocketServer.h"

std::uint16_t SocketServer::DEFAULT_PORT = 8080;

SocketServer::SocketServer()
	: SocketServer(DEFAULT_PORT) {}

SocketServer::SocketServer(std::uint16_t port)
	: m_port(port), m_socket(init(port)) {}

Socket SocketServer::accept() const
{
	return m_socket.accept();
}

Socket SocketServer::init(std::uint16_t port)
{
	struct addrinfo hints = { 0 };
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	auto addr = AddressInfo::get(NULL, std::to_string(port).c_str(), &hints);
	
	Socket listen_socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	listen_socket.bind(addr->ai_addr, static_cast<int>(addr->ai_addrlen));
	listen_socket.listen(SOMAXCONN);

	return listen_socket;
}
