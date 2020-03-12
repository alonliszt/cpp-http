#pragma once
#pragma push_macro("DELETE")
#undef DELETE

#include <iostream>

#include "../Common.h"
#include "Errors.h"

namespace HTTPMethod
{

	enum t : std::uint8_t
	{
		OPTIONS,
		GET,
		HEAD,
		POST,
		PUT,
		DELETE,
		TRACE,
		CONNECT
	};
}

namespace HTTP
{
	using Method = std::strong_enum<HTTPMethod::t>;

	HTTP::Method parse_method(std::string str);
}
#pragma pop_macro("DELETE")
