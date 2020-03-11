#pragma once

#include "../Common.h"

namespace HTTP
{
	struct Error : public std::runtime_error
	{
		Error(const std::string& msg) : std::runtime_error(msg) {}
	};

	class ErrorCode
		: public Error
	{
	public:
		ErrorCode(const std::string text, const std::string& msg, int status)
			: Error(std::format("% (status %)", msg, status)), status_text(text), m_status(status) {}

		inline int status() const { return m_status; }
		const std::string& to_string() const { return status_text; }

	private:
		const int m_status;
		const std::string status_text;
	};

	struct ServerError : public ErrorCode
	{
		ServerError(const std::string text, const std::string& msg, int status) : ErrorCode(text, msg, status) {}
	};

	struct ClientError : public ErrorCode
	{
		ClientError(const std::string text, const std::string& msg, int status) : ErrorCode(text, msg, status) {}
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

	struct NotImplemented : public ServerError
	{
		NotImplemented(const std::string& msg) : ServerError("Not Implemented", msg, 501) {}
	};
}