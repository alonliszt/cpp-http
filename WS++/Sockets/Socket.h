#pragma once
#include "SocketHeader.h"

#include "../Common.h"

class Socket
{
public:
	// Interface

private:
	// Inner members

public:
	struct Error
		: public StatusError
	{
		Error(const std::string& msg, int status) : StatusError(msg, status) {}
	};
};
