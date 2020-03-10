#pragma once

#include <vector>
#include <functional>

// Extending std with some more types
namespace std
{
	using bytes = std::vector<char>;

	template <class T>
	using predicate = std::function<bool(T)>;
}
