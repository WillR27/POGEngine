#pragma once

#include "PagoogCommon.h"

namespace Pagoog::Core
{
	class Window
	{
	public:
		static std::unique_ptr<Window> Create(std::string name);

		Window(std::string name);

		virtual ~Window() = default;

		virtual void Init() = 0;

		virtual bool ShouldClose() = 0;

		virtual ContextAddressFunc GetContextAddressFunc() const = 0;

		std::string GetName() const { return name; }

	private:
		std::string name;
	};
}

