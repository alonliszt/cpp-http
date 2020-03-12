#pragma once

#include "../Common.h"
#include "Socket.h"
class Socket;

class SocketReader
	: public ITextReader
{
public:
	SocketReader(const Socket& socket);

	std::bytes read(std::size_t len) override;

private:
	const Socket& m_socket;
};

class SocketWriter
	: public ITextWriter
{
public:
	SocketWriter(const Socket& socket);

	void write(std::bytes b) override;

private:
	const Socket& m_socket;
};
