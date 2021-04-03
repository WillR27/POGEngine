#pragma once

#include "POGMaths/Vectors.h"

namespace POG::Test
{
	using namespace Maths;

	TEST(VectorsTests, VectorsTest)
	{
		Vec3 asd = Cross(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f));
		EXPECT_EQ(asd, asd);
	}
}