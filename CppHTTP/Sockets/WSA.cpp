#include "WSA.h"

_WSA::_WSA()
{
	init();
}

_WSA::~_WSA()
{
	WSACleanup();
}

const volatile _WSA& _WSA::get_main()
{
	static _WSA wsa;
	return wsa;
}

void _WSA::init()
{
	int result = WSAStartup(MAKEWORD(2, 2), &m_data);
	if (result != 0)
	{
		throw Socket::Error("WSAStartup failed.", result);
	}
}

const WSADATA* _WSA::raw_data()
{
	return &m_data;
}
