#pragma once

#define POG_BIND_FN(fn)        [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define POG_STATIC_BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }

#define STRINGIFY(x) #x