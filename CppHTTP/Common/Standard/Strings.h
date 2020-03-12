#pragma once

#include <algorithm>
#include <cctype>
#include <locale>

namespace std
{
	inline void rtrim_inplace(std::string& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	inline void ltrim_inplace(std::string& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	inline std::string trim(std::string s)
	{
		ltrim_inplace(s);
		rtrim_inplace(s);
		return std::move(s);
	}

	inline bool isblank(std::string& s)
	{
		return std::find_if(s.begin(), s.end(), [](char c) { return !std::isspace(c); }) == s.end();
	}
}
