#pragma once

#include <iostream>

#include "../Common.h"
#include "Errors.h"

namespace HTTPVersion
{

	enum t : std::uint8_t
	{
		HTTP_1_0,
		HTTP_1_1
	};
}

namespace HTTP
{
	using Version = std::strong_enum<HTTPVersion::t>;

	HTTP::Version parse_version(std::string s);
}