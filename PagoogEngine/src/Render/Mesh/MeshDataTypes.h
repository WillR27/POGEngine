#pragma once

#include "Maths/Maths.h"

namespace PEngine
{
	class Vertex
	{
	public:
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

		class Index
		{
		public:
			typedef unsigned int ValueType;
			static const int Count = 1;
			static const int Size = sizeof(unsigned int) * Count;
		};
	};
}

