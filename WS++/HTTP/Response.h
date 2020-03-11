#pragma once

#include <string>

#include "Version.h"

namespace HTTP
{
	class Response
	{
	public:
		Response(int status, std::string response_text);
		Response() : Response(200, "OK") {}

		std::uint32_t status;
		std::string response_text;

		std::map<std::string, std::string> headers;

		const std::bytes& get_body() const;
		void set_body(std::bytes body);
		void set_body(std::string body);

		void write(ITextWriter& writer);

	private:
		std::bytes body;
	};
}
