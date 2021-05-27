#pragma once

namespace POG::Common
{
	using HashId = size_t;

	constexpr HashId HashStr(const char* str)
	{
		static_assert(sizeof(HashId) == 8 || sizeof(HashId) == 4);

		HashId h = 0;
		if constexpr (sizeof(HashId) == 8)
		{
			h = 1125899906842597L; // prime
		}
		else
		{
			h = 4294967291L;
		}

		int i = 0;
		while (str[i] != 0)
		{
			h = 31 * h + str[i++];
		}

		return h;
	}

	// Returns a hash id for the given type
	template <typename T, typename U = HashId>
	constexpr U Hash()
	{
		return HashStr(__FUNCSIG__);
	}
}