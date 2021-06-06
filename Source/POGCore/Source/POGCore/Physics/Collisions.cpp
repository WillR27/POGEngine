#include "POGCorePCH.h"
#include "Collisions.h"

namespace POG::Core
{
	RayResultRectCollider Hits(const Ray& ray, const Transform& transform, const RectCollider& rectCollider)
	{
		RayResultRectCollider result;

		// Position on a plane plus the normal to the plane = a representation of a plane
		// So we use the object's position
		// And by default assume that its front facing side is towards the camera
		POG::Maths::Vec3 positionOnPlane(transform.position);
		POG::Maths::Vec3 planeNormal(0.0f, 0.0f, -1.0f);
		planeNormal = POG::Maths::Normalise(transform.orientation) * planeNormal;

		// Do some maths stuff that I copied from the internet
		float numer = POG::Maths::DotProduct((positionOnPlane - ray.origin), planeNormal);
		float denom = POG::Maths::DotProduct(ray.direction, planeNormal);

		// Only allow if not 0 and we are looking at the front facing side
		if (denom < -0.00001f)
		{
			// This is the distance from the ray origin to the point on the plane
			float distance = numer / denom;

			// And this is the actual point of intersection
			result.pointOfIntersection = ray.origin + ray.direction * distance;

			// This is the point of intersection transformed back to the origin
			// This is so we can see if the point fits within the axis aligned version of the bounding box in 2D
			POG::Maths::Vec3 aa = POG::Maths::Inverse(transform.orientation) * (result.pointOfIntersection - transform.position);
			result.pointOnRect = POG::Maths::Vec2(aa.x, aa.y);

			// If we are inside, we have victory
			if (((result.pointOnRect.x >= rectCollider.min.x && result.pointOnRect.x <= rectCollider.max.x)
				|| (result.pointOnRect.x <= rectCollider.min.x && result.pointOnRect.x >= rectCollider.max.x))
				&& ((result.pointOnRect.y >= rectCollider.min.y && result.pointOnRect.y <= rectCollider.max.y)
					|| (result.pointOnRect.y <= rectCollider.min.y && result.pointOnRect.y >= rectCollider.max.y)))
			{
				result.hit = true;
			}
		}

		return result;
	}
}