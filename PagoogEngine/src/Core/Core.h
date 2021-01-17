#pragma once

#define PG_BIND_FN(fn)        [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define PG_STATIC_BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }

#define STRINGIFY(x) #x


template<typename T, typename O>
int IndexOf(const std::vector<T>& v, const O& object)
{
	auto it = std::find(v.begin(), v.end(), object);
	if (it != v.end())
	{
		return static_cast<int>(it - v.begin());
	}

	return -1;
}


template<typename T>
using Unique = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Unique<T> MakeUnique(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Shared<T> MakeShared(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using Weak = std::weak_ptr<T>;