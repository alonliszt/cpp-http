#include "HTTPRequest.h"

HTTP::Request::Request(ITextReader& reader)
	: m_reader(reader)
{
	parse_method();
	parse_headers();
}

void HTTP::Request::parse_method()
{
	std::regex regex("HTTP\\/(\\d\\.?\\d?) ([A-Za-z]+) (.+)");
	std::smatch match;

	std::string method_line = std::trim(m_reader.readline());
	
	if (!std::regex_match(method_line, match, regex))
	{
		throw HTTP::ParseError("Could not parse method line: " + method_line);
	}

	version = HTTP::parse_version(match[1].str());
	method = HTTP::parse_method(match[2].str());
	path = match[3].str();
}


void HTTP::Request::parse_headers()
{

}