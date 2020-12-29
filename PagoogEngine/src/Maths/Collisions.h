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

		AABB(Vec<D> min, Vec<D> max)
			: min(min)
			, max(max)
		{
			Vec<D> sizeVec;
			for (int d = 0; d < D; d++)
			{
				sizeVec[d] = static_cast<float>(abs(min[d] - max[d]));
			}

			//size = Size(sizeVec);
		}

		bool IsCollidingWith(const AABB<D>& aabb) const
		{
			for (int d = 0; d < D; d++)
			{
				if (GetMin()[d] > aabb.GetMax()[d] || GetMax()[d] < aabb.GetMin()[d])
				{
					return false;
				}
			}

			return true;
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

