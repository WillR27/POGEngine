#pragma once

namespace PEngine
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component();

		virtual std::string GetComponentName() const = 0;

		GameObject* gameObject = nullptr;
	};
}

