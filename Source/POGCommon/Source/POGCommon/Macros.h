#pragma once

#define POG_BIND_FN_THIS(fn)        [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define POG_BIND_FN(fn)					[](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }

#define STRINGIFY(x) #x