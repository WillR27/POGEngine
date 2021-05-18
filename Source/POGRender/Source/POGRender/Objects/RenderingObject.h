#pragma once

namespace POG::Render
{
	class RenderingObject
	{
	public:
		RenderingObject();
		virtual ~RenderingObject() = default;

		operator unsigned int() const { return id; }

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual RenderingObject* GetCurrent() = 0;

	protected:
		unsigned int id;
	};
}

