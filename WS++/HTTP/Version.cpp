#include "Version.h"

HTTP::Version parse_version(std::string s)
{
	if (s == "1.0")
	{
		return HTTPVersion::HTTP_1_0;
	}
	else if (s == "1.1")
	{
		return HTTPVersion::HTTP_1_1;
	}

	throw HTTP::VerisonError(std::format("Version % not supported", s));
}

HTTP::Version HTTP::parse_version(std::string s)
{
	if (s == "1.0")
	{
		return HTTPVersion::HTTP_1_0;
	}
	else if (s == "1.1")
	{
		return HTTPVersion::HTTP_1_1;
	}

	throw HTTP::VerisonError(std::format("Version % not supported", s));
}