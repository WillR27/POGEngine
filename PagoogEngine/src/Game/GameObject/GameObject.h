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

		template <typename T>
		const T* To() const
		{
			return dynamic_cast<const T*>(this);
		}

		void SetName(std::string name);
		std::string GetName() const;

	private:
		std::string name;
	};
}