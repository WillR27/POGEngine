#pragma once

#include "Maths/Maths.h"

namespace PEngine
{
	class Position
	{
	public:
		typedef float ValueType;
		static const int Count = 3;
		static const int Size = sizeof(float) * Count;
	};

	class Colour
	{
	public:
		typedef float ValueType;
		static const int Count = 3;
		static const int Size = sizeof(float) * Count;
	};
}

