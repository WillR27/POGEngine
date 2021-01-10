#pragma once

#include "Maths.h"

namespace PEngine
{
	struct Hit
	{
		Vec3 contactPoint = { 0.0f, 0.0f, 0.0f };
		Vec3 surfaceNormal = { 0.0f, 0.0f, 0.0f };
		Vec3 overlap = { 0.0f, 0.0f, 0.0f };
	};

	template<auto D>
	class AABB
	{
	public:
		AABB(Size<D> size)
			: size(size)
			, min(0.0f, 0.0f, 0.0f)
			, max(0.0f, 0.0f, 0.0f)
			, center(0.0f, 0.0f, 0.0f)
			, radii(0.0f, 0.0f, 0.0f)
		{
			for (int d = 0; d < D; d++)
			{
				radii[d] =  size[d] / 2.0f;
				min[d]   = -radii[d];
				max[d] = radii[d];
			}
		}

		AABB(Vec<D> min, Vec<D> max)
			: size({ 0.0f, 0.0f, 0.0f })
			, min(min)
			, max(max)
			, center(0.0f, 0.0f, 0.0f)
			, radii(0.0f, 0.0f, 0.0f)
		{
			Vec<D> sizeVec;
			for (int d = 0; d < D; d++)
			{
				float dx = abs(min[d] - max[d]);
				sizeVec[d] = static_cast<float>(dx);
				radii[d] = dx / 2.0f;
				center[d] = min[d] + radii[d];
			}

			size = Size(sizeVec);
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

		Shared<Hit> IsCollidingWith2(const AABB<D>& aabb) const
		{
			float dy = aabb.center.y - this->center.y;
			float py = (this->radii.y + aabb.radii.y) - abs(dy);
			if (py <= 0.0f) return nullptr;

			float dx = aabb.center.x - this->center.x;
			float px = (this->radii.x + aabb.radii.x) - abs(dx);
			if (px <= 0.0f) return nullptr;

			float dz = aabb.center.z - this->center.z;
			float pz = (this->radii.z + aabb.radii.z) - abs(dz);
			if (pz <= 0.0f) return nullptr;

			Hit hit;
			if (py < px && py < pz)
			{
				int sy = Maths::Sign(dy);
				hit.overlap.y = py * sy;
				hit.surfaceNormal.y = static_cast<float>(sy);
				hit.contactPoint.x = aabb.center.x;
				hit.contactPoint.y = this->center.y + (this->radii.y * sy);
				hit.contactPoint.z = aabb.center.z;
			}
			else if (px < py && px < pz)
			{
				int sx = Maths::Sign(dx);
				hit.overlap.x = px * sx;
				hit.surfaceNormal.x = static_cast<float>(sx);
				hit.contactPoint.x = this->center.x + (this->radii.x * sx);
				hit.contactPoint.y = aabb.center.y;
				hit.contactPoint.z = aabb.center.z;
			}
			else
			{
				int sz = Maths::Sign(dz);
				hit.overlap.z = pz * sz;
				hit.surfaceNormal.z = static_cast<float>(sz);
				hit.contactPoint.x = aabb.center.x;
				hit.contactPoint.y = aabb.center.y;
				hit.contactPoint.z = this->center.z + (this->radii.z * sz);
			}

			return MakeShared<Hit>(hit);
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

		Vec<D> GetCenter() const
		{
			return center;
		}

		Vec<D> GetRadii() const
		{
			return radii;
		}

	private:
		Size<D> size;
		Vec<D> min, max;
		Vec<D> center;
		Vec<D> radii;
	};
}

