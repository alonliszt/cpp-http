#pragma once
#include "SocketHeader.h"

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

#include <memory>

#include "Socket.h"

class AddressInfo
{
public:
	using T = addrinfo;
	using Ptr = T*;

	static void free(Ptr ptr);

private:
	class Deleter
	{
	public:
		void operator()(AddressInfo::Ptr t);
	};

public:
	using AutoDelete = std::unique_ptr<T, Deleter>;

	static AutoDelete get(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA* pHints);
};

