#pragma once

#include "Maths.h"

namespace PEngine
{
	template<auto D>
	class AABB
	{
	public:
		AABB(Size<D> size)
			: size(size)
		{
			for (int i = 0; i < D; i++)
			{
				min[i] = -size[i] / 2.0f;
				max[i] =  size[i] / 2.0f;
			}
		}

		Size<D> GetSize() const
		{
			return size;
		}

		Vec<D> GetMin() const
		{
			return min;
		}

		Vec<D> GetMax() const
		{
			return max;
		}

	private:
		Size<D> size;
		Vec<D> min, max;
	};
}

