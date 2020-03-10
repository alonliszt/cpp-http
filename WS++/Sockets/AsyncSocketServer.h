#pragma once

#include <thread>

#include "SocketServer.h"

class AsyncSocketServer
{
public:
	using handler_func = std::function<void(Socket&)>;

	AsyncSocketServer(std::uint16_t port);

	void set_handler(handler_func handler);
	void serve_forever();

private:
	SocketServer m_server;
	std::unique_ptr<std::thread> m_accept_thread;

	handler_func m_handler;

	void accept_loop();
	void client_thread(Socket s);
};