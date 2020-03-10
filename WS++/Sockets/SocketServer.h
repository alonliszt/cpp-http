#pragma once

#include "AddresInfo.h"
#include "Socket.h"

class SocketServer
{
public:
	SocketServer();
	SocketServer(std::uint16_t port);

	// Consts
	static std::uint16_t DEFAULT_PORT;

	Socket accept() const;

private:
	std::uint16_t m_port;
	Socket m_socket;

	Socket init(std::uint16_t port);
};