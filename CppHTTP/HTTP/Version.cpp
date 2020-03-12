#include "Version.h"

std::map<std::string, HTTP::Version> version_map
{
	{ "1.0", HTTPVersion::HTTP_1_0 },
	{ "1.1", HTTPVersion::HTTP_1_1 }
};

HTTP::Version HTTP::parse_version(std::string s)
{
	auto el = version_map.find(s);
	if (el == version_map.end())
	{
		throw HTTP::VersionNotSupported(std::format("Version % not supported", s));
	}

	return (*el).second;
}
