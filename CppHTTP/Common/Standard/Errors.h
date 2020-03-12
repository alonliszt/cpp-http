#pragma once

#include <stdexcept>

#include "Format.h"

class StatusError
	: public std::runtime_error
{
public:
	StatusError(const std::string& msg, int status)
		: std::runtime_error(std::format("% (status %)", msg, status)), m_status(status) {}

	inline int status() const { return m_status; }

private:
	const int m_status;
};
