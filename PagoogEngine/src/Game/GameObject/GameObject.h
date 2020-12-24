#pragma once

namespace PEngine
{
	class GameObject
	{
	public:
		virtual ~GameObject() = default;

		template <typename T>
		T* To()
		{
			return dynamic_cast<T*>(this);
		}
	};
}