#pragma once

#include "POGRender/Shader/Shader.h"

#include "POGMaths.h"

#include <map>
#include <memory>
#include <string>

namespace POG::Render
{
	class Material
	{
	public:
		Material();
		
		~Material();

		void UpdateShaderUniforms();

		std::string GetName() const { return name; }

		Shader& GetShader() const { return *shader; }
		void SetShader(std::shared_ptr<Shader> shader);

		const std::map < std::string, Maths::Vec4 > GetColours() const { return colours; }
		void AddColour(std::string name, Maths::Vec4 colour = Maths::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
		void SetColour(std::string name, Maths::Vec4 colour);

	private:
		std::string name;

		std::shared_ptr<Shader> shader;

		std::map<std::string, Maths::Vec4> colours;
	};
}