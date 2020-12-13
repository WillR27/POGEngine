#include "pgepch.h"
#include "CoreRenderingUtil.h"

namespace PEngine
{
	ScopedBind::ScopedBind(RenderingObject& renderingObject)
		: renderingObject(renderingObject)
	{
		previousRenderingObject = renderingObject.GetCurrent();
		renderingObject.Bind();
	}

	ScopedBind::~ScopedBind()
	{
		if (previousRenderingObject != nullptr)
		{
			previousRenderingObject->Bind();
		}
		else
		{
			renderingObject.Unbind();
		}
	}
}
