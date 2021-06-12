#include "POGCorePCH.h"
#include "Collisions.h"

#include "POGCore/Application/Application.h"

namespace POG::Core
{
	RayResultRectCollider Hits(const Ray& ray, const Transform& transform, const RectCollider& rectCollider, const Sprite& sprite)
	{
		float ratioX = sprite.texture->GetWidth() / Sprite::PixelToUnitRatio;
		float ratioY = sprite.texture->GetHeight() / Sprite::PixelToUnitRatio;
		
		RectCollider collider = rectCollider;
		collider.min.x *= ratioX;
		collider.max.x *= ratioX;
		collider.min.y *= ratioY;
		collider.max.y *= ratioY;

		return Hits(ray, transform, collider);
	}

	RayResultRectCollider Hits(const Ray& ray, const Transform& transform, const RectCollider& rectCollider)
	{
		RayResultRectCollider result;

		RectCollider collider = rectCollider;
		collider.min.x *= transform.scale.x;
		collider.max.x *= transform.scale.x;
		collider.min.y *= transform.scale.y;
		collider.max.y *= transform.scale.y;

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
			if (((result.pointOnRect.x >= collider.min.x && result.pointOnRect.x <= collider.max.x)
				|| (result.pointOnRect.x <= collider.min.x && result.pointOnRect.x >= collider.max.x))
				&& ((result.pointOnRect.y >= collider.min.y && result.pointOnRect.y <= collider.max.y)
					|| (result.pointOnRect.y <= collider.min.y && result.pointOnRect.y >= collider.max.y)))
			{
				result.hit = true;
			}
		}

		return result;
	}

	Ray CalcMouseRay(Maths::Vec3 origin)
	{
		// Normalise mouse coords to OpenGL style
		float x = ((Core::Input::GetMouseX() * 2.0f) / Core::Application::GetInstance().GetWidth()) - 1.0f;
		float y = 1.0f - ((Core::Input::GetMouseY() * 2.0f) / Core::Application::GetInstance().GetHeight());

		// 1.0f to represent into the screen
		POG::Maths::Vec4 clip(x, y, 1.0f, 1.0f);

		// To eye space
		POG::Maths::Vec4 eye = POG::Maths::Inverse(POG::Core::Camera::MainCamera->GetProjection()) * clip;
		eye.z = 1.0f;
		eye.w = 0.0f;

		// To world space
		POG::Maths::Vec4 world = POG::Maths::Inverse(POG::Core::Camera::MainCamera->GetView()) * eye;
		POG::Maths::Vec3 direction(world.x, world.y, world.z);
		direction = POG::Maths::Normalise(direction);

		POG::Core::Ray ray
		{
			.origin = origin,
			.direction = direction,
		};

		return ray;
	}
}