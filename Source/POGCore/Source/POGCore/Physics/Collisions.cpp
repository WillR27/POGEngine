#include "POGCorePCH.h"
#include "Collisions.h"

#include "POGCore/Application/Application.h"

namespace POG::Core
{
	///////////////////////////////////////////////////////////////////////////////
	// HELPERS

	bool Contains(Maths::Vec2 min, Maths::Vec2 max, Maths::Vec2 point)
	{
		return ((point.x >= min.x && point.x <= max.x) || (point.x <= min.x && point.x >= max.x))
			&& ((point.y >= min.y && point.y <= max.y) || (point.y <= min.y && point.y >= max.y));
	}

	RectCollider TranslateRectCollider(const RectCollider& rectCollider, const Maths::Vec3& translation)
	{
		return RectCollider();
	}

	BoxCollider2D ScaleBoxCollider2D(const BoxCollider2D& boxCollider, const Maths::Vec3& scale)
	{
		BoxCollider2D collider = boxCollider;
		collider.min.x *= scale.x;
		collider.max.x *= scale.x;
		collider.min.y *= scale.y;
		collider.max.y *= scale.y;

		return collider;
	}

	RectCollider ScaleRectCollider(const RectCollider& rectCollider, const Maths::Vec3& scale)
	{
		RectCollider collider = rectCollider;
		collider.min.x *= scale.x;
		collider.max.x *= scale.x;
		collider.min.y *= scale.y;
		collider.max.y *= scale.y;

		return collider;
	}

	// HELPERS
	///////////////////////////////////////////////////////////////////////////////

	RayResultRectCollider Hits(const Ray& ray, const Transform& transform, const RectCollider& rectCollider, const Sprite& sprite)
	{
		float ratioX = sprite.texture->GetWidth() / sprite.pixelsToUnitsRatio;
		float ratioY = sprite.texture->GetHeight() / sprite.pixelsToUnitsRatio;
		
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

		RectCollider collider = ScaleRectCollider(rectCollider, transform.scale);

		// Position on a plane plus the normal to the plane = a representation of a plane
		// So we use the object's position
		// And by default assume that its front facing side is towards the camera
		Maths::Vec3 positionOnPlane(transform.position);
		Maths::Vec3 planeNormal(0.0f, 0.0f, -1.0f);
		planeNormal = transform.orientation * planeNormal;

		// Do some maths stuff that I copied from the internet
		float numer = Maths::DotProduct((positionOnPlane - ray.origin), planeNormal);
		float denom = Maths::DotProduct(ray.direction, planeNormal);

		// Only allow if not 0 and we are looking at the front facing side
		if (denom < -0.00001f)
		{
			// This is the distance from the ray origin to the point on the plane
			float distance = numer / denom;

			// And this is the actual point of intersection
			result.pointOfIntersection = ray.origin + ray.direction * distance;

			// This is the point of intersection transformed back to the origin
			// This is so we can see if the point fits within the axis aligned version of the bounding box in 2D
			Maths::Vec3 axisAligned = Maths::Inverse(transform.orientation) * (result.pointOfIntersection - transform.position);
			result.pointOnRect = Maths::Vec2(axisAligned.x, axisAligned.y);

			// If we are inside, we have victory
			if (Contains(collider.min, collider.max, result.pointOnRect))
			{
				result.hit = true;
			}
		}

		return result;
	}

	Ray CalcMouseRay(Maths::Vec3 origin)
	{
		// TODO: Use Mouse::Normalise() instead
		// Normalise mouse coords to OpenGL style
		float x = ((Core::Mouse::GetX() * 2.0f) / Core::Application::GetInstance().GetWidth()) - 1.0f;
		float y = 1.0f - ((Core::Mouse::GetY() * 2.0f) / Core::Application::GetInstance().GetHeight());

		// 1.0f to represent into the screen
		Maths::Vec4 clip(x, y, 1.0f, 1.0f);

		// To eye space
		Maths::Vec4 eye = Maths::Inverse(Core::Camera::MainCamera->GetProjection()) * clip;
		eye.z = 1.0f;
		eye.w = 0.0f;

		// To world space
		Maths::Vec4 world = Maths::Inverse(Core::Camera::MainCamera->GetView()) * eye;
		Maths::Vec3 direction(world.x, world.y, world.z);
		direction = Maths::Normalise(direction);

		Core::Ray ray
		{
			.origin = origin,
			.direction = direction,
		};

		return ray;
	}

	CollisionResult TestCollision(Maths::Vec2 position1, const std::vector<Maths::Vec2>& points1, Maths::Vec2 position2, const std::vector<Maths::Vec2>& points2)
	{
		CollisionResult result;

		Maths::Vec2 position = position1;
		std::vector<Maths::Vec2> pointsOne = points1;
		std::vector<Maths::Vec2> pointsTwo = points2;

		for (int shape = 0; shape < 2; shape++)
		{
			if (shape == 1)
			{
				position = position2;
				pointsOne = points2;
				pointsTwo = points1;
			}

			for (int i = 0; i < pointsOne.size(); i++)
			{
				Maths::Vec2 point1 = pointsOne[i];

				for (int j = 0; j < pointsTwo.size(); j++)
				{
					Maths::Vec2 point2A = pointsTwo[j];
					Maths::Vec2 point2B = pointsTwo[(j + 1) % pointsTwo.size()];

					float h = (point2B.x - point2A.x) * (position.y - point1.y) - (position.x - point1.x) * (point2B.y - point2A.y);
					float t1 = ((point2A.y - point2B.y) * (position.x - point2A.x) + (point2B.x - point2A.x) * (position.y - point2A.y)) / h;
					float t2 = ((position.y - point1.y) * (position.x - point2A.x) + (point1.x - position.x) * (position.y - point2A.y)) / h;

					if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
					{
						result.collision = true;
						result.displacement.x = (1.0f - t1) * (point1.x - position.x);
						result.displacement.y = (1.0f - t1) * (point1.y - position.y);
						result.displacement.x *= (shape == 0 ? -1 : +1);
						result.displacement.y *= (shape == 0 ? -1 : +1);
						return result;
					}
				}
			}
		}

		return result;
	}

	CollisionResult TestCollisionBoxCollider2D(const Transform& transform1, const BoxCollider2D& boxCollider1, const Transform& transform2, const BoxCollider2D& boxCollider2)
	{
		std::vector<Maths::Vec2> points1 
		{  
			transform1.ApplyTransform({ boxCollider1.min.x, boxCollider1.min.y }),
			transform1.ApplyTransform({ boxCollider1.min.x, boxCollider1.max.y }),
			transform1.ApplyTransform({ boxCollider1.max.x, boxCollider1.max.y }),
			transform1.ApplyTransform({ boxCollider1.max.x, boxCollider1.min.y }),
		};

		std::vector<Maths::Vec2> points2
		{
			transform2.ApplyTransform({ boxCollider2.min.x, boxCollider2.min.y }),
			transform2.ApplyTransform({ boxCollider2.min.x, boxCollider2.max.y }),
			transform2.ApplyTransform({ boxCollider2.max.x, boxCollider2.max.y }),
			transform2.ApplyTransform({ boxCollider2.max.x, boxCollider2.min.y }),
		};

		return TestCollision({ transform1.position.x, transform1.position.y }, points1, { transform2.position.x, transform2.position.y }, points2);
	}

	CollisionResult Hits(const Transform& transform1, const RectCollider& rectCollider1, const Transform& transform2, const RectCollider& rectCollider2)
	{
		CollisionResult result;

		RectCollider collider1 = ScaleRectCollider(rectCollider1, transform1.scale);
		Maths::Vec3 min1 = Maths::Vec3(collider1.min.x, collider1.min.y, 0.0f) * transform1.orientation;
		Maths::Vec3 max1 = Maths::Vec3(collider1.max.x, collider1.max.y, 0.0f) * transform1.orientation;
		min1 += transform1.position;
		max1 += transform1.position;

		RectCollider collider2 = ScaleRectCollider(rectCollider2, transform2.scale);
		Maths::Vec3 min2 = Maths::Vec3(collider2.min.x, collider2.min.y, 0.0f) * transform2.orientation;
		Maths::Vec3 max2 = Maths::Vec3(collider2.max.x, collider2.max.y, 0.0f) * transform2.orientation;
		min2 += transform2.position;
		max2 += transform2.position;

		Maths::Vec3 pointOnPlane1 = min1;
		Maths::Vec3 planeNormal1(0.0f, 0.0f, -1.0f);
		planeNormal1 = transform1.orientation * planeNormal1;

		Maths::Vec3 pointOnPlane2 = min2;
		Maths::Vec3 planeNormal2(0.0f, 0.0f, -1.0f);
		planeNormal2 = transform2.orientation * planeNormal2;

		float dot = Maths::DotProduct(planeNormal1, planeNormal2);

		// TODO: Transform to 2D and try collision detection as they are essentially parallel
		if (dot < 0.0001f)
		{
			return result;
		}

		// Get some plane equations we can use
		// Given a normal n = (A, B, C) and a point p = (x0, y0, z0)
		// The equation for a plane is A(x - x0) + B(y - y0) + C(z - z0) = 0
		// So we are looking for an equation like in the form ax + by + cz + d = 0
		// E.g. x + 3y -7z - 21 = 0
		// Any values that satisfy the equation are a point on the plane
		float a1 = planeNormal1.x;
		float b1 = planeNormal1.y;
		float c1 = planeNormal1.z;
		float d1 = (a1 * -pointOnPlane1.x) + (b1 * -pointOnPlane1.y) + (c1 * -pointOnPlane1.z);
		float a2 = planeNormal2.x;
		float b2 = planeNormal2.y;
		float c2 = planeNormal2.z;
		float d2 = (a2 * -pointOnPlane2.x) + (b2 * -pointOnPlane2.y) + (c2 * -pointOnPlane2.z);

		// Now can work out the line of intersection between these two planes
		// This is in the form (q0, r0, s0) + t(u0, v0, w0)
		// Given that a1x + b1y + c1z + d1 = 0 and a2x + b2y + c2z + d2 = 0
		// Let z = t
		// So  a1x + b1y = -c1t - d1 
		// and a2x + b2y = -c2z - d2
		// Solve simultaneously
		float a11 = a1 * a2;
		float b11 = b1 * a2;
		float c11 = c1 * a2;
		float d11 = d1 * a2;
		float a21 = a2 * a1;
		float b21 = b2 * a1;
		float c21 = c2 * a1;
		float d21 = d2 * a1;

		// Subtract second equation from first to get y = C1z + D1
		float B1 = b11 - b21;
		float C1 = (c11 - c21) / B1;
		float D1 = (d11 - d21) / B1;

		// Repeat pattern to get x = C2z + D2
		float a12 = a1 * b2;
		float b12 = b1 * b2;
		float c12 = c1 * b2;
		float d12 = d1 * b2;
		float a22 = a2 * b1;
		float b22 = b2 * b1;
		float c22 = c2 * b1;
		float d22 = d2 * b1;

		// Subtract second equation from first to get x = C2z + D2
		float A2 = a12 - a22;
		float C2 = (c12 - c22) / A2;
		float D2 = (d12 - d22) / A2;

		// So our final line equation looks like
		// (q0, r0, s0) + t(u0, v0, w0)
		float q0 = D2;
		float r0 = D1;
		float s0 = 0.0f; // Because z = 0 + 1t
		float u0 = C2;
		float v0 = C1;
		float w0 = 1.0f; // Because z = 0 + 1t

		// Now we want reduce this to a 2D problem
		// Where the rectangle is assumed to have a direction of (0, 0, -1)
		Maths::Vec3 qrs(q0, r0, s0);
		Maths::Vec3 uvw(u0, v0, w0);
		Maths::Vec3 colliderCenter1(max1 - min1);
		Maths::Vec3 colliderCenter2(max2 - min2);
		Maths::Vec3 qrs1 = Maths::Inverse(transform1.orientation) * (qrs - colliderCenter1);
		Maths::Vec3 qrs2 = Maths::Inverse(transform2.orientation) * (qrs - colliderCenter2);
		Maths::Vec3 uvw1 = Maths::Inverse(transform1.orientation) * (uvw - colliderCenter1);
		Maths::Vec3 uvw2 = Maths::Inverse(transform2.orientation) * (uvw - colliderCenter2);
		Maths::Vec2 qr1(qrs1.x, qrs1.y);
		Maths::Vec2 qr2(qrs2.x, qrs2.y);
		Maths::Vec2 uv1(uvw1.x, uvw1.y);
		Maths::Vec2 uv2(uvw2.x, uvw2.y);

		return result;
	}
}
