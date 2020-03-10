#pragma once

#include <vector>
#include <functional>

// Extending std with some more types
namespace std
{
	using bytes = std::vector<char>;

	template <class T>
	using predicate = std::function<bool(T)>;

	template <class T>
	class strong_enum
	{
	public:
		strong_enum() = default;
		constexpr strong_enum(T content) : data(content) {}

		operator T() const { return data; }
		explicit operator bool() = delete;

	private:
		T data;
	};
}
