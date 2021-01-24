#pragma once

#include "Maths/Maths.h"
#include "Render/Shader/Shader.h"

namespace PEngine
{
	class Material
	{
	public:
		Material();
		~Material();

		void UpdateShaderUniforms();

		std::string GetName() const { return name; }

		Shader& GetShader() const { return *shader; }
		void SetShader(Shared<Shader> shader);

		const std::map<std::string, Vec4> GetColours() const { return colours; }
		void AddColour(std::string name, Vec4 colour = Vec4(0.0f, 0.0f, 0.0f, 1.0f));
		void SetColour(std::string name, Vec4 colour);

	private:
		std::string name;

		Shared<Shader> shader;

		std::map<std::string, Vec4> colours;
	};
}

