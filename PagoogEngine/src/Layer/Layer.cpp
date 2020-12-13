#include "pgepch.h"
#include "Layer.h"

namespace PEngine
{
	Layer::Layer(const char* name)
		: name(name)
	{
	}

	const char* Layer::GetName() const
	{
		return name;
	}
}