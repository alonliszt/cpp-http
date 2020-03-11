#pragma once

#include <string>
#include <sstream>

namespace std
{
	template <class T>
	void _format_stream(ostringstream& output, istringstream& input, T arg)
	{
		std::string token;
		std::getline(input, token, '%');

		output << token;
		output << arg;
	}

	template <class T, class ... Args>
	void _format_stream(ostringstream& output, istringstream& input, T arg1, Args ... args)
	{
		_format_stream(output, input, arg1);
		_format_stream(output, input, args...);
	}

	/// <summary>
	/// Formats a string
	/// Given a format string with '%' as format characters and a list of arguments, returns a string with %s substituted with argument values.
	/// </summary>
	/// <param name="format_str">Format string</param>
	/// <param name="...args">Argument of arbitrary types which for `ostringstream &lt;&lt; arg` is supported</param>
	/// <returns></returns>
	template <class ... Args>
	std::string format(std::string format_str, Args ... args)
	{
		std::istringstream input(format_str);
		std::ostringstream output;

		_format_stream(output, input, args...); // Formatting all arguments

		std::string leftover(input.str().substr(input.tellg()));
		output << leftover;

		return output.str();
	}
}
