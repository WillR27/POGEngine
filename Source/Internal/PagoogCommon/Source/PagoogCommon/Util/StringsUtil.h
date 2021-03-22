#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "PagoogCommonAPI.h"

namespace Pagoog::Common
{
	// TODO: Just here to get the dll/lib to build
	PG_COMMON_API void Placeholder();

	template <typename... Args>
	static std::string Format(const std::string& format, Args... args)
	{
		int size = snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
		if (size <= 0) { throw std::runtime_error("Error during formatting."); }
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}
}