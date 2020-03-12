#pragma once

#include <WinSock2.h>
#include <Windows.h>

#include <iostream>

#include "Socket.h"

class _WSA
{
public:
	const WSADATA* raw_data();
	
	/// <summary>
	/// A call to this function validates that WSAStartup has been called.
	/// WSACleanup is automatically called when the program terminates.
	/// </summary>
	/// <returns>A reference to the WSADATA object</returns>
	static const volatile _WSA& get_main();

private:
	_WSA();
	~_WSA();

	void init();

	WSADATA m_data;
};

