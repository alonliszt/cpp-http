#include "HTTPMethod.h"

HTTP::Method HTTP::parse_method(std::string str)
{
	if (str == "OPTIONS") return HTTPMethod::OPTIONS;
	else if (str == "GET") return HTTPMethod::GET;
	else if (str == "HEAD") return HTTPMethod::HEAD;
	else if (str == "POST") return HTTPMethod::POST;
	else if (str == "PUT") return HTTPMethod::PUT;
	else if (str == "DELETE") return HTTPMethod::DELETE;
	else if (str == "TRACE") return HTTPMethod::TRACE;
	else if (str == "CONNECT") return HTTPMethod::CONNECT;
	else
		throw HTTP::MethodError("Could not parse HTTP method " + str);
}
