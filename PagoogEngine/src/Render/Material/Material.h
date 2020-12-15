#pragma once

#include "Maths/Maths.h"

namespace PEngine
{
	class Material
	{
	public:
		Material(std::string name);
		~Material();

		void AddColour(std::string name, Vec4 colour = Vec4(0.0f, 0.0f, 0.0f, 1.0f));
		void SetColour(std::string name, Vec4 colour);
		const std::map<std::string, Vec4> GetColours() const;

	private:
		std::string name;

		std::map<std::string, Vec4> colours;
	};
}

