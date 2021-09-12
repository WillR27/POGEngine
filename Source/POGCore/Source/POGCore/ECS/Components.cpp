#include "POGCorePCH.h"
#include "Components.h"

namespace POG::Core
{
	const float Sprite::PixelsToUnitsRatio = 100.0f / 1.0f; // 100 pixels for every 1 unit in game
	
	// TODO: Improve, maybe move to POGMaths along with Transform
	Maths::Vec2 ApplyTransform(Maths::Vec2 vec, Transform transform)
	{
		Maths::Mat4 modelMatrix = Maths::ToModelMatrix(transform.position, transform.orientation, transform.scale);
		Maths::Vec4 newVec(vec.x, vec.y, 0.0f, 1.0f);
		newVec = modelMatrix * newVec;

		return { newVec.x, newVec.y };
	}
}