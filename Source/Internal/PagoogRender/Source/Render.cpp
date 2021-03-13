#include "PagoogRenderPCH.h"
#include "Render.h"

#include <glad/glad.h>

namespace Pagoog::Render
{
	void Render::SetContextAddressFunc(ContextAddressFunc func)
	{
		gladLoadGLLoader((GLADloadproc)func);
	}
}