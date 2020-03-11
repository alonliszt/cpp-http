#pragma once

#include <string>
#include <sstream>

#include "../Standard/Types.h"

class IWriter
{
public:
	virtual void write(std::bytes b) = 0;

	virtual void write(char c)
	{
		write(std::bytes{ c });
	}
};

class ITextWriter
	: public IWriter
{
public:
	virtual void write_str(std::string s)
	{
		write(std::bytes(s.begin(), s.end()));
	}
};

class IReader
{
public:
	virtual std::bytes read(std::size_t len) = 0;

	// Should be re-implemented for efficiency for most classes
	virtual int read()
	{
		std::bytes b = read(1);
		if (b.size() == 0)
			return std::char_traits<char>::eof();

		return static_cast<int>(b[0]);
	}
};

class ITextReader
	: public IReader
{
public:
	virtual std::string read_str(std::size_t len)
	{
		std::bytes b = read(len);
		if (b.size() == 0)
			return "";

		return std::string(b.begin(), b.end());
	}

	virtual std::string read_until(std::predicate<int> pred)
	{
		int next;
		std::ostringstream s;

		while (!pred(next = read()) && next != std::char_traits<char>::eof())
		{
			s.put(static_cast<char>(next));
		}

		return s.str();
	}

	virtual std::string read_until(int barrier)
	{
		return read_until([barrier](int c) { return c == barrier;  });
	}

	virtual std::string readline()
	{
		char lst = '\0';
		return read_until([&lst](int c) {
			bool success = c == '\n' && lst == '\r';
			lst = static_cast<char>(c);
			return success;
		});
	}

	virtual std::string readword()
	{
		return read_until([](int c) { return std::isspace(c); });
	}
};
