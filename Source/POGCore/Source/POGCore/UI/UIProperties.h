#pragma once

namespace POG::Core
{
	enum class ScaleMode
	{
		Fixed,
		Stretch,
	};

	enum Anchor
	{
		None	= 0x01,
		Left    = 0x02,
		Top     = 0x04,
		Right   = 0x08,
		Bottom  = 0x10,
	};

	inline Anchor operator&(Anchor a, Anchor b)
	{
		return static_cast<Anchor>(static_cast<int>(a) & static_cast<int>(b));
	}

	inline Anchor operator|(Anchor a, Anchor b)
	{
		return static_cast<Anchor>(static_cast<int>(a) | static_cast<int>(b));
	}

	enum class Dock
	{

	};
}