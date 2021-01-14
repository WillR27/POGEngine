#pragma once

namespace PEngine
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component();

		virtual Component* Clone() const = 0;

		virtual std::string GetComponentName() const = 0;

		GameObject* gameObject = nullptr;
	};
}

