#pragma once

#include "PagoogMaths/Vectors.h"

namespace Pagoog::Test
{
	using namespace Maths;

	TEST(VectorsTests, VectorsTest)
	{
		Vec3 asd = Cross(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f));
		EXPECT_EQ(asd, asd);
		EXPECT_EQ(asd, Vec3(1.0f, 1.0f, 11.0f));
	}
}