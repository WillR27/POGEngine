#pragma once

#include "Render/Core/Objects/RenderingObject.h"

namespace PEngine
{
	/// <summary>
	/// Used to bind an object for the given scope, then bind whatever was previously bound again.
	/// </summary>
	class ScopedBind
	{
	public:
		ScopedBind(RenderingObject& renderingObject);
		~ScopedBind();

	private:
		RenderingObject& renderingObject;
		RenderingObject* previousRenderingObject;
	};
}

