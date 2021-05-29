#pragma once

#include "POGCore.h"

namespace POG::Editor
{
	class Component
	{
	public:
		Component()
			: hasChanged(false)
		{
		}

		virtual void Render() = 0;

		bool HasChanged() const { return hasChanged; }
		void SetChanged() { hasChanged = true; }

	protected:
		bool hasChanged;
	};

	class AttachedCamera : public Component
	{
	public:
		AttachedCamera(Core::AttachedCamera camera)
			: camera(camera)
		{
		}

		void Render() override;

		Core::AttachedCamera GetCamera() const { return camera; }

	private:
		Core::AttachedCamera camera;
	};

	class Transform : public Component
	{
	public:
		Transform(Core::Transform transform)
			: transform(transform)
		{
		}

		void Render() override;

		Core::Transform GetTransform() const { return transform; }

	private:
		Core::Transform transform;
	};
}