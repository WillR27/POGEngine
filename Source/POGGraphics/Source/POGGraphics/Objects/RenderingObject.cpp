#include "POGGraphicsPCH.h"
#include "RenderingObject.h"

namespace POG::Graphics
{
	RenderingObject::RenderingObject()
		: id(0)
	{
	}

	RenderingObject::RenderingObject(const RenderingObject& renderingObject)
		: id(renderingObject.id)
	{
	}
}