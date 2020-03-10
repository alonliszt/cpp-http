#pragma once

#include <string>
#include <regex>

#include "../Common.h"
#include "HTTPErrors.h"
#include "HTTPVersion.h"
#include "HTTPMethod.h"

namespace HTTP
{
	class Request
	{
	public:
		Request(ITextReader& reader);

		HTTP::Version version;
		HTTP::Method method;
		std::string path;

	private:
		void parse_method();
		void parse_headers();

		ITextReader& m_reader;
	};
}
