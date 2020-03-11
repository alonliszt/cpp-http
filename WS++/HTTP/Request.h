#pragma once

#include <string>
#include <regex>
#include <map>

#include "../Common.h"
#include "Errors.h"
#include "Version.h"
#include "Method.h"

namespace HTTP
{
	class Request
	{
	public:
		Request(ITextReader& reader);

		HTTP::Version version;
		HTTP::Method method;
		std::string path;
		std::map<std::string, std::string> headers;

	private:
		void parse_method();
		void parse_headers();

		ITextReader& m_reader;
	};
}
