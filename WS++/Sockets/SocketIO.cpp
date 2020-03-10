#include "SocketIO.h"

SocketReader::SocketReader(const Socket& socket)
	: m_socket(socket) {}

std::bytes SocketReader::read(std::size_t len)
{
	return m_socket.recv(static_cast<int>(len));
}

SocketWriter::SocketWriter(const Socket& socket)
	: m_socket(socket) {}

void SocketWriter::write(std::bytes b)
{
	m_socket.send(b);
}
