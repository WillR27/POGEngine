#include "POGGraphicsPCH.h"
#include "RenderingObject.h"

namespace POG::Graphics
{
	RenderingObject::RenderingObject()
		: id(0)
	{
	}

	RenderingObject::RenderingObject(const RenderingObject& renderingObject)
		: SharedObject::SharedObject(renderingObject)
		, id(renderingObject.id)
	{
	}

	RenderingObject& RenderingObject::operator=(const RenderingObject& renderingObject)
	{
		SharedObject::operator=(renderingObject);

		this->id = renderingObject.id;

		return *this;
	}
}