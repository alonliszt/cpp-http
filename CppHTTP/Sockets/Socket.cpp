#include "Socket.h"

const int Socket::MAX_RECEIVE_LENGTH = 1024;

Socket::Socket(SOCKET soc)
	: m_socket(soc)
{
	if (soc == INVALID_SOCKET)
	{
		throw Socket::Error("Cannot create a socket object with INVALID_SOCKET handle", 0);
	}
}

Socket::Socket(Socket&& other) noexcept
	: m_socket(other.m_socket)
{
	// Invalidating the other object so it doesn't contain our new SOCKET object
	other.m_socket = INVALID_SOCKET;
}

Socket::Socket(int af, int type, int protocol)
	: Socket(create_raw_socket(af, type, protocol)) {}

const Socket& Socket::operator=(Socket&& other) noexcept
{
	std::swap(m_socket, other.m_socket);
	return *this;
}

Socket::~Socket()
{
	if (is_valid())
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

bool Socket::is_valid() const
{
	return m_socket != INVALID_SOCKET;
}

void Socket::bind(sockaddr* name, int namelen)
{
	int status = ::bind(m_socket, name, namelen);
	if (status == SOCKET_ERROR)
	{
		throw Socket::Error("Failed to bind address to socket listener", WSAGetLastError());
	}
}

void Socket::listen(int backlog)
{
	int status = ::listen(m_socket, backlog);
	if (status == SOCKET_ERROR)
	{
		throw Socket::Error("Failed to listen on socket", WSAGetLastError());
	}
}

Socket Socket::accept() const
{
	SOCKET s = ::accept(m_socket, nullptr, nullptr);
	if (s == INVALID_SOCKET)
	{
		throw Socket::Error("Could not accept socket", WSAGetLastError());
	}
	return Socket(s);
}

void Socket::send(std::bytes content) const
{
	int status = ::send(m_socket, &content[0], static_cast<int>(content.size()), 0);
	if (status == SOCKET_ERROR)
	{
		throw Socket::Error("Could not send bytes on socket", WSAGetLastError());
	}
}

std::bytes Socket::recv(int len) const
{
	if (len <= 0 || len > Socket::MAX_RECEIVE_LENGTH)
	{
		throw Socket::Error(std::format("Invalid length supplied to Socket::read (%)", len), 0);
	}

	char buffer[Socket::MAX_RECEIVE_LENGTH];
	int bytes_read = ::recv(m_socket, buffer, len, 0);

	if (bytes_read == -1)
		throw Socket::Error("Could not read from socket", WSAGetLastError());

	return std::bytes(std::begin(buffer), std::begin(buffer) + bytes_read);
}

SocketReader Socket::create_reader() const
{
	return SocketReader(*this);
}

SocketWriter Socket::create_writer() const
{
	return SocketWriter(*this);
}

std::tuple<SocketReader, SocketWriter> Socket::create_io() const
{
	return { create_reader(), create_writer() };
}

std::string Socket::to_string() const
{
	return std::format("<Socket %>", static_cast<int>(m_socket));
}

SOCKET Socket::raw_socket() const
{
	return m_socket;
}

SOCKET Socket::create_raw_socket(int af, int type, int protocol)
{
	// Ensuring WSAStartup had been called
	_WSA::get_main();
	return ::socket(af, type, protocol);
}