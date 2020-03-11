#include "Request.h"

HTTP::Request::Request(ITextReader& reader)
	: m_reader(reader)
{
	parse_method();
	parse_headers();
}

void HTTP::Request::parse_method()
{
	std::regex regex("([A-Za-z]+) ([^\\s]+) HTTP\\/(\\d\\.?\\d?)");
	std::smatch match;

	std::string method_line = std::trim(m_reader.readline());
	
	if (!std::regex_match(method_line, match, regex))
	{
		throw HTTP::ParseError("Could not parse method line: " + method_line);
	}

	method = HTTP::parse_method(match[1].str());
	path = match[2].str();
	version = HTTP::parse_version(match[3].str());
}


void HTTP::Request::parse_headers()
{
	std::string line;

	std::string key;
	std::string value;

	while ((line = m_reader.readline()).size() > 0)
	{
		// Check if the line is a continuation line, then append the line to the previous key
		if (std::isspace(line[0]))
		{
			std::ltrim_inplace(line);
			headers[key] += line;
			continue;
		}

		// Otherwise, parse the line as a new header line
		auto colon_index = std::find(line.begin(), line.end(), ':');
		if (colon_index == line.end())
		{
			throw HTTP::ParseError("Could not parse header line: " + line);
		}

		key = std::string(line.begin(), colon_index);
		value = std::string(colon_index + 1, line.end());
		std::ltrim_inplace(value);

		headers[key] = value;

	}
	std::cout << "End of headers" << std::endl;
}