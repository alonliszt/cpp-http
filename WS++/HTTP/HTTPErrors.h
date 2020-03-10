#pragma once

#include "../Common.h"

namespace HTTP
{
	struct Error : public std::runtime_error
	{
		Error(const std::string& msg) : std::runtime_error(msg) {}
	};

	struct ParseError : public HTTP::Error
	{
		ParseError(const std::string& msg) : Error(msg) {}
	};

	struct VerisonError : public HTTP::Error
	{
		VerisonError(const std::string& msg) : Error(msg) {}
	};

	struct MethodError : public HTTP::Error
	{
		MethodError(const std::string& msg) : Error(msg) {}
	};
}