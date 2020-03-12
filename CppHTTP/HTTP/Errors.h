#pragma once

#include "../Common.h"

#define ERROR_CODE_T(_name)\
struct _name : public ErrorCode\
{\
_name(const std::string& text, const std::string& msg, int status) : ErrorCode(text, msg, status) {}\
};

#define ERROR_CODE_M(_base, _name, _text, _number)\
struct _name : public _base\
{\
_name(const std::string& msg) : _base(_text, msg, _number) {}\
}

#define ERROR_CODE_S(_base, _name, _number)\
struct _name : public _base\
{\
_name(const std::string& msg) : _base(#_name, msg, _number) {}\
}

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


	class ErrorCode
		: public Error // Does it have to inherit std::runtime_error at all?
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

	ERROR_CODE_T(Informational);
	ERROR_CODE_T(Success);
	ERROR_CODE_T(Redirection);
	ERROR_CODE_T(ClientError);
	ERROR_CODE_T(ServerError);

	ERROR_CODE_S(Informational, Continue, 100);
	ERROR_CODE_M(Informational, SwitchingProtocols, "Switching Protocols", 101);
	ERROR_CODE_S(Success, OK, 200);
	ERROR_CODE_S(Success, Created, 201);
	ERROR_CODE_S(Success, Accepted, 202);
	ERROR_CODE_M(Success, NonAuthoritiveInformation, "Non-Authoritive Information", 203);
	ERROR_CODE_M(Success, NoContent, "No Content", 204);
	ERROR_CODE_M(Success, ResetContent, "Reset Content", 205);
	ERROR_CODE_M(Success, PartialContent, "Partial Content", 205);
	ERROR_CODE_M(Redirection, MultipleChoices, "Multiple Choices", 300);
	ERROR_CODE_M(Redirection, MovedPermanently, "Moved Permanently", 301);
	ERROR_CODE_S(Redirection, Found, 302);
	ERROR_CODE_M(Redirection, SeeOther, "See Other", 303);
	ERROR_CODE_M(Redirection, NotModified, "Not Modified", 304);
	ERROR_CODE_M(Redirection, UseProxy, "Use Proxy", 305);
	ERROR_CODE_M(Redirection, TemporaryRedirect, "Temporary Redirect", 307);
	ERROR_CODE_M(ClientError, BadRequest, "Bad Request", 400);
	ERROR_CODE_S(ClientError, Unauthorized, 401);
	ERROR_CODE_M(ClientError, PaymentRequired, "Payment Required", 402);
	ERROR_CODE_S(ClientError, Forbidden, 403);
	ERROR_CODE_M(ClientError, NotFound, "Not Found", 404);
	ERROR_CODE_M(ClientError, MethodNotAllowed, "Method Not Allowed", 405);
	ERROR_CODE_M(ClientError, NotAcceptable, "Not Acceptable", 406);
	ERROR_CODE_M(ClientError, ProxyAuthenticationRequired, "Proxy Authentication Required", 407);
	ERROR_CODE_M(ClientError, RequestTimeOut, "Request Time-out", 408);
	ERROR_CODE_S(ClientError, Conflict, 409);
	ERROR_CODE_S(ClientError, Gone, 410);
	ERROR_CODE_M(ClientError, LengthRequired, "Length Required", 411);
	ERROR_CODE_M(ClientError, PreconditionFailed, "Precondition Failed", 412);
	ERROR_CODE_M(ClientError, RequestEntityTooLarge, "Request Entity Too Large", 413);
	ERROR_CODE_M(ClientError, RequestURITooLarge, "Request-URI Too Large", 414);
	ERROR_CODE_M(ClientError, UnsupportedMediaType, "Unsupported Media Type", 415);
	ERROR_CODE_M(ClientError, RequestRangeNotSatisfiable, "Request range not satisfiable", 416);
	ERROR_CODE_M(ClientError, ExpectationFailed, "Expectation Failed", 417);
	ERROR_CODE_M(ServerError, InternalServerError, "Internal Server Error", 500);
	ERROR_CODE_M(ServerError, NotImplemented, "NotImplemented", 501);
	ERROR_CODE_M(ServerError, BadGateway, "Bad Gateway", 502);
	ERROR_CODE_M(ServerError, ServiceUnavailable, "Service Unavailable", 503);
	ERROR_CODE_M(ServerError, GatewayTimeout, "Gateway Time-Out", 504);
	ERROR_CODE_M(ServerError, VersionNotSupported, "HTTP Version Not Supported", 505);
}