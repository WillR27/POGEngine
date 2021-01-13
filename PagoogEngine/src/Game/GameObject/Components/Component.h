#pragma once

namespace PEngine
{
	class GameObject;

	class _Component
	{
	public:
		virtual ~_Component();

		virtual _Component* Clone() const = 0;

		virtual std::string GetComponentName() const = 0;

		GameObject* gameObject = nullptr;
	};

	template <typename T>
	class Component
	{
	public:
		Component(T* component)
			: component(component)
		{
		}

		/// <summary>
		/// Used to access the underlying component.
		/// </summary>
		T* operator->()
		{
			return component;
		}

		/// <summary>
		/// Returns the underlying component pointer.
		/// </summary>
		T* operator&()
		{
			return component;
		}

		/// <summary>
		/// Returns the underlying component object;
		/// </summary>
		T& operator*()
		{
			return *component;
		}

		/// <summary>
		/// Returns whether the component exists.
		/// </summary>
		bool Exists()
		{
			return component != nullptr;
		}

	private:
		T* component;
	};
}

