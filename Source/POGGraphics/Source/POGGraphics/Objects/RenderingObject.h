#pragma once

#include "POGCommon.h"

namespace POG::Graphics
{
	class RenderingObject : public Common::Disposable
	{
	public:
		RenderingObject();
		virtual ~RenderingObject() = default;

		virtual void Dispose() = 0;

		operator unsigned int() const { return id; }

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual RenderingObject* GetCurrent() = 0;

	protected:
		unsigned int id;
	};
}

