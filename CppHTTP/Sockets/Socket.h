#pragma once
#include "SocketHeader.h"

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

#include "../Common.h"
#include "SocketIO.h"
class SocketReader;
class SocketWriter;
#include "WSA.h"

class Socket
{
public:
	// Constructors and assignments
	explicit Socket(SOCKET soc);
	Socket(int af, int type, int protocol);
	~Socket();

	Socket(const Socket& other) = delete;
	Socket(Socket&& other) noexcept;

	const Socket& operator=(const Socket& other) = delete;
	const Socket& operator=(Socket&& other) noexcept;

	// Consts
	static const int MAX_RECEIVE_LENGTH;

	// Interface
	bool is_valid() const;
	void bind(sockaddr* name, int namelen);
	void listen(int backlog);
	
	Socket accept() const;

	void send(std::bytes content) const;
	std::bytes recv(int len) const;

	SocketReader create_reader() const;
	SocketWriter create_writer() const;
	std::tuple<SocketReader, SocketWriter> create_io() const;

	std::string to_string() const;
	SOCKET raw_socket() const;

private:
	// Inner members
	SOCKET m_socket;

	static SOCKET create_raw_socket(int af, int type, int protocol);

public:
	struct Error
		: public StatusError
	{
		Error(const std::string& msg, int status) : StatusError(msg, status) {}
	};
};
