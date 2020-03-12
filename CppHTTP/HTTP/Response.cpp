#include "Response.h"

HTTP::Response::Response(int status, std::string response_text)
	: status(status), response_text(response_text), headers{
		{ "Server", "C++ WebServer" },
		{ "Content-Type", "text/plain; utf-8" },
} {}

HTTP::Response::Response(const HTTP::ErrorCode& error)
	: status(error.status()), response_text(error.to_string()) {}

const std::bytes& HTTP::Response::get_body() const
{
	return body;
}

void HTTP::Response::set_body(std::bytes _body)
{
	body = _body;
	headers["Content-Length"] = std::to_string(_body.size());
}

void HTTP::Response::set_body(std::string _body)
{
	set_body(std::bytes(_body.begin(), _body.end()));
}

void HTTP::Response::write(ITextWriter& writer)
{
	writer.write_str(std::format("HTTP/1.1 % %\n", status, response_text));
	for (auto& header : headers)
	{
		writer.write_str(std::format("%: %\n", header.first, header.second));
	}

	writer.write_str("\r\n");
	writer.write(body);
}
