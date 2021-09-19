#pragma once

#include "POGCommon.h"

namespace POG::Graphics
{
	class RenderingObject : public Common::Disposable, public Common::SharedObject
	{
	public:
		RenderingObject();
		RenderingObject(const RenderingObject& renderingObject);
		RenderingObject(RenderingObject&& renderingObject) = delete;

		virtual ~RenderingObject() = default;

		RenderingObject& operator=(const RenderingObject& renderingObject);

		virtual void Dispose() = 0;

		operator unsigned int() const { return id; }

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual RenderingObject* GetCurrent() = 0;

	protected:
		unsigned int id;
	};
}

