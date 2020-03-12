#include "AsyncSocketServer.h"

AsyncSocketServer::AsyncSocketServer(std::uint16_t port)
	: m_server(port), m_handler(nullptr) {}

void AsyncSocketServer::set_handler(AsyncSocketServer::handler_func func)
{
	m_handler = func;
}

void AsyncSocketServer::serve_forever()
{
	// Implementation might change
	accept_loop();
}

void AsyncSocketServer::accept_loop()
{
	while (true)
	{
		Socket s = m_server.accept();
		std::thread(&AsyncSocketServer::client_thread, this, std::move(s)).detach();
	}
}

void AsyncSocketServer::client_thread(Socket s)
{
	if (m_handler != nullptr)
	{
		m_handler(s);
	}
}